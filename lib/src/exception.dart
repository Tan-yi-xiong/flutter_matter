
const successCode = 0;
const argsInvalid = 1;
const methodNoFound = 2;
const unHandlerException = -99;

class CallPlatformException {
  final String message;
  CallPlatformException(this.message);
}