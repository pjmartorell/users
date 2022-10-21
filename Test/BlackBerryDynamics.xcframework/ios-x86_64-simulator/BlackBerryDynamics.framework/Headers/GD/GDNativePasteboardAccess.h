/*
* (c) 2020 BlackBerry Limited. All rights reserved.
*
*/

#import <Foundation/Foundation.h>
/** Use the Pasteboard in the clear while DLP is turned on.
*
*/

@interface GDNativePasteboardAccess : NSObject

/** Use the Pasteboard in the clear while DLP is turned on.
* This \ss_function allows pasteboard items to be written to and read from the pasteboard in the clear while Data Leakage Prevention * is active.
* Pasteboard items within the <tt>action</tt> block will NOT be encrypted when placed on the pasteboard.
*
* @param action  Pasteboard actions to be performed on the pasteboard in the clear while Data Leakage Prevention is turned on.\n
*/

+ (void)performActionOnNativePasteboard:(void (^)(void))action;

@end
