const successCode = 0;
const argsInvalid = 1;
const methodNoFound = 2;
const unHandlerException = -99;

/// Exception raised when a platform request or callback returns an error.
///
/// [message] remains the human-readable message used by existing callers.
/// New code can use [code], [methodName], and [details] to inspect the failure
/// without parsing [message] or including sensitive request parameters.
class CallPlatformException implements Exception {
  final String message;
  final int? code;
  final String? methodName;
  final Map<String, Object?>? details;

  /// The underlying failure, when one exists.
  ///
  /// This value is intentionally excluded from [toString] and from the
  /// structured logging helper so callers cannot accidentally log a payload
  /// embedded in a lower-level exception.
  final Object? cause;

  CallPlatformException(
    this.message, {
    this.code,
    this.methodName,
    this.details,
    this.cause,
  });

  /// Alias for [details] used by callers that prefer the platform data name.
  Map<String, Object?>? get data => details;

  @override
  String toString() => message;
}

/// Exception raised when the native platform returns an invalid envelope.
///
/// The [violation] must describe the protocol problem only. It must not
/// contain the raw response or request payload.
class PlatformProtocolException extends CallPlatformException
    implements FormatException {
  final String violation;

  /// The malformed value, when safe to retain.
  ///
  /// Callers must not pass the raw native response or request payload here so
  /// secrets cannot leak through logging or error reporting.
  @override
  final Object? source;

  /// The offset associated with [source], when available.
  @override
  final int? offset;

  PlatformProtocolException(
    this.violation, {
    int? code,
    String? methodName,
    Object? cause,
    this.source,
    this.offset,
  }) : super(
          'Invalid platform response envelope: $violation',
          code: code,
          methodName: methodName,
          details: const <String, Object?>{
            'category': 'protocol-violation',
          },
          cause: cause,
        );
}
