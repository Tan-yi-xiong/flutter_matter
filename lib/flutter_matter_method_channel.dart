/// MethodChannel transport entry point.
///
/// The declarations live with [FlutterMatterPlatform] so the interface can
/// expose the transport surface without importing its concrete implementation.
library flutter_matter_method_channel;

export 'flutter_matter_platform_interface.dart' show MethodChannelFlutterMatter;
export 'src/platform_transport_types.dart'
    show
        MethodCallHandler,
        PlatformCallResult,
        PlatformResult,
        RequestPlatformParams,
        TransportObject,
        createRequestPlatformUrl;
