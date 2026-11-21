package com.tyx.flutter_matter

import matter.onboardingpayload.DiscoveryCapability
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFailsWith
import kotlin.test.assertFalse
import kotlin.test.assertSame
import kotlin.test.assertTrue

internal class FlutterMatterPluginTest {
  @Test
  fun controllerLifecycle_allowsOnlyOneActiveController() {
    val gate = ControllerLifecycleGate<String, String>()

    assertTrue(gate.beginCreation("owner-a"))
    assertFalse(gate.beginCreation("owner-b"))
    gate.activate("handle-a", "controller-a", "owner-a")

    assertEquals(ControllerLifecycleGate.State.ACTIVE, gate.currentState())
    assertFalse(gate.beginCreation("owner-b"))
    assertSame("controller-a", gate.findActiveController("handle-a", "owner-a"))
  }

  @Test
  fun controllerLifecycle_isolatesControllerOwner() {
    val gate = ControllerLifecycleGate<String, String>()
    assertTrue(gate.beginCreation("owner-a"))
    gate.activate("handle-a", "controller-a", "owner-a")

    assertTrue(gate.isOwnerActive("owner-a"))
    assertFalse(gate.isOwnerActive("owner-b"))
    assertEquals(null, gate.findActiveController("handle-a", "owner-b"))
  }

  @Test
  fun controllerLifecycle_canRecoverFromAbortedCreation() {
    val gate = ControllerLifecycleGate<String, String>()

    assertTrue(gate.beginCreation("owner-a"))
    assertTrue(gate.cancelCreation("owner-a"))

    assertEquals(ControllerLifecycleGate.State.EMPTY, gate.currentState())
    assertTrue(gate.beginCreation("owner-b"))
  }

  @Test
  fun controllerLifecycle_activationOwnerMismatchCanBeCleanedUp() {
    val gate = ControllerLifecycleGate<String, String>()
    assertTrue(gate.beginCreation("owner-a"))

    assertFailsWith<IllegalStateException> {
      gate.activate("handle-a", "controller-a", "owner-b")
    }

    assertEquals(ControllerLifecycleGate.State.CREATING, gate.currentState())
    assertFalse(gate.cancelCreation("owner-b"))
    assertTrue(gate.cancelCreation("owner-a"))
    assertEquals(ControllerLifecycleGate.State.EMPTY, gate.currentState())
  }

  @Test
  fun controllerLifecycle_handleMismatchLeavesActiveControllerUntouched() {
    val gate = ControllerLifecycleGate<String, String>()
    assertTrue(gate.beginCreation("owner-a"))
    gate.activate("handle-a", "controller-a", "owner-a")

    val decision = gate.beginShutdown("handle-b", "owner-a")

    assertEquals(ControllerLifecycleGate.ShutdownDecision.HandleMismatch, decision)
    assertEquals(ControllerLifecycleGate.State.ACTIVE, gate.currentState())
    assertSame("controller-a", gate.findActiveController("handle-a", "owner-a"))
  }

  @Test
  fun controllerLifecycle_ownerMismatchLeavesActiveControllerUntouched() {
    val gate = ControllerLifecycleGate<String, String>()
    assertTrue(gate.beginCreation("owner-a"))
    gate.activate("handle-a", "controller-a", "owner-a")

    val decision = gate.beginShutdown(expectedOwner = "owner-b")

    assertEquals(ControllerLifecycleGate.ShutdownDecision.OwnerMismatch, decision)
    assertEquals(ControllerLifecycleGate.State.ACTIVE, gate.currentState())
    assertSame("controller-a", gate.findActiveController("handle-a", "owner-a"))
  }

  @Test
  fun controllerLifecycle_successfulShutdownAllowsNextController() {
    val gate = ControllerLifecycleGate<String, String>()
    assertTrue(gate.beginCreation("owner-a"))
    gate.activate("handle-a", "controller-a", "owner-a")

    val decision = gate.beginShutdown("handle-a", "owner-a")
    val ready = decision as ControllerLifecycleGate.ShutdownDecision.Ready
    assertEquals("handle-a", ready.handle)
    assertSame("controller-a", ready.controller)

    assertTrue(gate.completeShutdown("handle-a"))
    assertEquals(ControllerLifecycleGate.State.EMPTY, gate.currentState())
    assertEquals(
      ControllerLifecycleGate.ShutdownDecision.NoActiveController,
      gate.beginShutdown("handle-a", "owner-a"),
    )
    assertTrue(gate.beginCreation("owner-b"))
  }

  @Test
  fun controllerLifecycle_shutdownFailurePermanentlyBlocksCreation() {
    val gate = ControllerLifecycleGate<String, String>()
    assertTrue(gate.beginCreation("owner-a"))
    gate.activate("handle-a", "controller-a", "owner-a")
    gate.beginShutdown("handle-a", "owner-a")

    gate.failShutdown()

    assertEquals(ControllerLifecycleGate.State.POISONED, gate.currentState())
    assertFalse(gate.beginCreation("owner-a"))
    assertEquals(
      ControllerLifecycleGate.ShutdownDecision.Poisoned,
      gate.beginShutdown("handle-a", "owner-a"),
    )
  }

  @Test
  fun controllerLifecycle_invalidShutdownCompletionPoisonsRuntime() {
    val gate = ControllerLifecycleGate<String, String>()
    assertTrue(gate.beginCreation("owner-a"))
    gate.activate("handle-a", "controller-a", "owner-a")
    gate.beginShutdown("handle-a", "owner-a")

    assertFalse(gate.completeShutdown("handle-b"))

    assertEquals(ControllerLifecycleGate.State.POISONED, gate.currentState())
    assertFalse(gate.beginCreation("owner-a"))
  }

  @Test
  fun controllerLifecycle_rejectedSubmissionOnlyPoisonsWhenInUse() {
    val emptyGate = ControllerLifecycleGate<String, String>()
    assertFalse(emptyGate.poisonIfInUse())
    assertEquals(ControllerLifecycleGate.State.EMPTY, emptyGate.currentState())

    val activeGate = ControllerLifecycleGate<String, String>()
    assertTrue(activeGate.beginCreation("owner-a"))
    activeGate.activate("handle-a", "controller-a", "owner-a")
    assertTrue(activeGate.poisonIfInUse())
    assertEquals(ControllerLifecycleGate.State.POISONED, activeGate.currentState())
    assertFalse(activeGate.beginCreation("owner-b"))
  }

  @Test
  fun engineRegistry_returnsRemainingChannelAfterOwnerDetach() {
    val registry = EngineSessionRegistry<String, String>()
    registry.register("owner-a", "channel-a")
    registry.register("owner-b", "channel-b")

    assertTrue(registry.isRegistered("owner-a"))
    assertEquals(2, registry.count())
    assertEquals("channel-b", registry.unregister("owner-a"))
    assertFalse(registry.isRegistered("owner-a"))
    assertEquals("channel-b", registry.channelFor("owner-b"))
    assertEquals(null, registry.unregister("owner-b"))
    assertEquals(0, registry.count())
  }

  @Test
  fun jsonNumberToByte_acceptsIntegralBoundaries() {
    assertEquals(0.toByte(), jsonNumberToByte(0))
    assertEquals(0.toByte(), jsonNumberToByte(0L))
    assertEquals(0.toByte(), jsonNumberToByte(0.0))
    assertEquals(127.toByte(), jsonNumberToByte(127.toByte()))
    assertEquals(255.toByte(), jsonNumberToByte(255))
    assertEquals(255.toByte(), jsonNumberToByte(255L))
    assertEquals(255.toByte(), jsonNumberToByte(255.0))
  }

  @Test
  fun jsonNumberToByte_rejectsInvalidValues() {
    val invalidValues = listOf<Any?>(
      -1,
      -1L,
      -1.0,
      256,
      256L,
      256.0,
      0.5,
      254.999,
      Double.NaN,
      Double.POSITIVE_INFINITY,
      Double.NEGATIVE_INFINITY,
      "1",
      null,
      true,
    )

    invalidValues.forEach { value ->
      assertFailsWith<IllegalArgumentException> {
        jsonNumberToByte(value)
      }
    }
  }

  @Test
  fun discoveryCapabilities_useDartWireValues() {
    assertEquals(
      listOf(1, 2, 3),
      discoveryCapabilitiesToDart(
        listOf(
          DiscoveryCapability.SOFT_AP,
          DiscoveryCapability.BLE,
          DiscoveryCapability.ON_NETWORK,
        )
      )
    )
  }

  @Test
  fun discoveryCapabilities_ignoreUnsupportedUpstreamValues() {
    assertEquals(
      listOf(2),
      discoveryCapabilitiesToDart(
        listOf(
          DiscoveryCapability.NFC,
          DiscoveryCapability.BLE,
          DiscoveryCapability.WIFI_PAF,
        )
      )
    )
  }
}
