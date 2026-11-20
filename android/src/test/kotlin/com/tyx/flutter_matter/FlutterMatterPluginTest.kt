package com.tyx.flutter_matter

import matter.onboardingpayload.DiscoveryCapability
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFailsWith

internal class FlutterMatterPluginTest {
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
