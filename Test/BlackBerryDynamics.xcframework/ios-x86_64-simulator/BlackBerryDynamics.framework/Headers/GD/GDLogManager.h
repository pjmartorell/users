/*
 * (c) 2017 BlackBerry Limited. All rights reserved.
 */

#import <Foundation/Foundation.h>

/** BlackBerry Dynamics log upload state.
 *
 * \copydetails ssGDLogManagerUploadState
 */
typedef NS_ENUM(NSInteger, GDLogUploadState)
{
    /** Log upload hasn't been started.
     *
     * This is the initial state.
     */
    GDLogUploadStateIdle       = 0,

    /** Log upload has been started and is now underway.
     */
    GDLogUploadStateInProgress = 100,

    /** Log upload has finished.
     */
    GDLogUploadStateCompleted  = 200,

    /** The last log upload operation was cancelled.
     * 
     * A new upload hasn't been started.
     */
    GDLogUploadStateCancelled  = 300,

    /** Log upload has been started but is currently suspended.
     */
    GDLogUploadStateSuspended  = 400,

    /** Log upload was suspended but has now been resumed.
     */
    GDLogUploadStateResumed    = 500,
};

/** Notification name for BlackBerry Dynamics activity log upload progress.
 * 
 * Use this value to add an <tt>NSNotificationCenter</tt> observer of BlackBerry
 * Dynamics activity log upload progress. See the \ref GDLogManager class
 * reference for details.
 */
extern NSString * const GDLogUploadNotification;

/** Maximum duration of user detailed logging.
 *
 * The maximum duration for which detailed logging can be switched on by
 * the \ref GDLogManager.detailedLoggingFor: \ss_function.
 * 
 * \internal Proposed by Jim, 15 min is considered a reasonable max duration that discourages users from leaving detailed logging on for too long.
 */
extern const NSTimeInterval GDLogManagerDetailedMaximumDuration;

/** BlackBerry Dynamics log manager.
 *
 * \copydetails ssGDLogManager
 */
@interface GDLogManager : NSObject

/** Current activity log upload state.
 * 
 *  @return GDLogUploadState value representing the current upload state.
 */
@property (nonatomic, readonly) GDLogUploadState uploadState;

/** Amount of activity log data uploaded so far.
 *
 * @return <tt>NSInteger</tt> representing the amount of data sent so far, in
 *         bytes.
 */
@property (nonatomic, readonly) NSInteger          uploadBytesSent;

/** Total amount of activity log data to upload.
 *
 * @return <tt>NSInteger</tt> representing the total data to be sent, in bytes.
 */
@property (nonatomic, readonly) NSInteger          uploadBytesTotal;

/** Get a reference to the BlackBerry Dynamics activity log manager object.
 * 
 * This \ss_function returns a reference to the BlackBerry Dynamics activity log
 * manager object. The activity log manager is a "singleton class".
 *
 * @return Reference that can be used to call, for example, the
 *         \ref startUpload \ss_function.
 */
+ (instancetype)sharedInstance;

/** Upload current activity logs.
 *
 * \copydetails ssGDLogManagerStartUpload
 */
- (BOOL)startUpload;

/** Cancel activity log upload.
 *
 * \copydetails ssGDLogManagerCancelUpload
 */
- (BOOL)cancelUpload;

/** Suspend activity log upload.
 *
 * \copydetails ssGDLogManagerSuspendUpload
 */
- (BOOL)suspendUpload;

/** Resume activity log upload.
 *
 * \copydetails ssGDLogManagerResumeUpload
 */
- (BOOL)resumeUpload;

/** Switch on detailed activity logging in the BlackBerry Dynamics Runtime.
 * 
 * \copydetails ssGDLogManagerDetailedLoggingFor
 */
- (BOOL)detailedLoggingFor:(NSTimeInterval) duration;

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
/** Open the built-in activity log upload user interface.
 *
 * \copydetails ssGDLogManagerOpenLogUploadUI
 */
- (BOOL)openLogUploadUI;
#endif
@end
