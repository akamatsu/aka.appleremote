#import <IOKit/IOKitLib.h>
#import <IOKit/IOCFPlugIn.h>
#import <IOKit/hid/IOHIDLib.h>
#import <IOKit/hid/IOHIDKeys.h>

Boolean initAppleRemote(void);
void terminateAppleRemote(void);
void setExclusiveMode(Boolean flag);
void startListening(void);
void stopListening(void);
void setCallBack(void *func, void *refCon);
