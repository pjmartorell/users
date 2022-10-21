/*
 * (c) 2017 BlackBerry Limited. All rights reserved.
 *
 */

#pragma once

#import <Foundation/Foundation.h>
#import "GDPortability.h"

NS_ASSUME_NONNULL_BEGIN

/** File handle access to the secure file system.
 * 
 * This class is a subclass of the native <tt>NSFileHandle</tt> class, for
 * access to the BlackBerry Dynamics secure file system.
 * 
 * <h2>Secure File System</h2>
 * \copydetails ssGDFileSystem
 *
 * \divclass{bulletlists}
 * <h2>Usage</h2>
 * This class is a subclass of the native <tt>NSFileHandle</tt> class. It should
 * be easy to replace references to <tt>NSFileHandle</tt> with references to
 * <tt>GDFile</tt><tt>Handle</tt>, in order to convert code that utilizes the
 * native file system into code that utilizes the secure file system.
 *
 * The differences between this class and <tt>NSFileHandle</tt> are:
 * - Only files can be represented, not sockets nor other types of data stream.
 * - Read and write access is limited to the secure store.
 * - Extracted file descriptors can only be used with BlackBerry Dynamics
 *   programming interfaces, see below.
 * - The "factory" style initializers, for example
 *   <tt>fileHandleWithStandardError</tt>, cannot be used.
 * - The asynchronous communication \ss_functions cannot be used.
 * - The <tt>NSFile</tt> notifications are never dispatched.
 * - Error codes could be in the specific <TT>GDFil</TT><TT>eManager</TT> error
 *   domain, or could be general <TT>NS</TT> error codes.
 * .
 * 
 * File descriptors extracted from instances of this class can only be used with
 * this class, and with other BlackBerry Dynamics programming interfaces such as
 * the BlackBerry Dynamics C language programming interface. They cannot be used
 * with, for example, the native POSIX programming interfaces, nor with
 * <tt>NSFileHandle</tt>.
 *   
 * \error_param_intro
 *
 * The programming interface of this class has the same semantics as the base
 * class. The documentation of this class lists the elements of the programming
 * interface but doesn't describe them. See the documentation of the base class,
 * <tt>NSFileHandle</tt>, for descriptions.
 * \enddivclass
 *
 * @see <a
 *          HREF="https://developer.apple.com/reference/foundation/nsfilehandle"
 *          target="blank"
 *      >NSFileHandle class reference</a> on the apple.com developer website.
 * @see \ref gdfilemanagererrordomain
 * @see <a
 *          HREF="https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/ErrorHandlingCocoa/ErrorHandling/ErrorHandling.html"
 *          target="_blank"
 *      >Error Handling Programming Guide</A> on the apple.com developer
 *      website.
 * @see \ss_sqldatabase_link
 * @see \ref GDPersistentStoreCoordinator
 * @see \ref GDFileManager
 * @see \ref capilist
  * 
 * \snippets_intro
 * In each snippet, a function that uses native file handles is converted to use
 * secure file handles instead. The conversion is simple.
 *
 * \snippet{Create file from NSData and read back}
 * The second function in the snippet is the original; the third is the
 * converted version. The changed line is flagged with a comment. The first
 * function in the snippet is a utility that is used by both the original and
 * the converted function, with no changes.
 * \code
 * - (NSString *)documentsFolderPathForFileNamed:(NSString *)fileName
 * {
 *     NSArray *paths =
 *     NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
 *                                         NSUserDomainMask,
 *                                         YES);
 *     NSString *documentsDirectory = [paths objectAtIndex:0];
 *     return [documentsDirectory stringByAppendingPathComponent:fileName];
 * }
 *
 * - (NSString *)writeAndReadWithNSFileHandle
 * {
 *     NSString *text = @"Text that is not protected.";
 *     NSData *fileData = [text dataUsingEncoding:NSUTF8StringEncoding];
 *
 *     NSString* filePath = [self documentsFolderPathForFileNamed:@"MyFile.txt"]
 *
 *     BOOL fileCreated = [[NSFileManager defaultManager] createFileAtPath:filePath
 *                                                        contents:fileData
 *                                                        attributes:nil];
 *      
 *     NSFileHandle* fileHandle = [NSFileHandle fileHandleForReadingAtPath:filePath];
 *     NSData* resData = [fileHandle availableData];
 *
 *     NSString *myString = [[NSString alloc] initWithData:resData encoding:NSUTF8StringEncoding];
 *
 *     return myString;
 * }
 *
 * - (NSString *)writeAndReadWithGDFileHandle
 * {
 *     NSString *text = @"Text that is to be protected by GD SDK.";
 *     NSData *fileData = [text dataUsingEncoding:NSUTF8StringEncoding];
 *
 *     NSString* filePath = [self documentsFolderPathForFileNamed:@"MyFile.txt"]
 *
 *     // Following uses GDFileManager instead of NSFileManager.
 *     BOOL fileCreated = [[GDFileManager defaultManager] createFileAtPath:filePath
 *                                                        contents:fileData
 *                                                        attributes:nil];
 *
 *     // Following uses GDFileHandle instead of NSFileHandle.
 *     GDFileHandle* fileHandle = [GDFileHandle fileHandleForReadingAtPath:filePath];
 *     NSData* resData = [fileHandle availableData];
 *
 *     NSString *myString = [[NSString alloc] initWithData:resData encoding:NSUTF8StringEncoding];
 *
 *     return myString;
 * }
 * \endcode
 *
 * \snippet{Create file by writing and read back}
 * The second function in the snippet is the original; the third is the
 * converted version. The changed line is flagged with a comment. The first
 * function in the snippet is a utility that is used by both the original and
 * the converted function, with no changes.
 * \code
 * - (NSString *)documentsFolderPathForFileNamed:(NSString *)fileName
 * {
 *     NSArray *paths =
 *     NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
 *                                         NSUserDomainMask,
 *                                         YES);
 *     NSString *documentsDirectory = [paths objectAtIndex:0];
 *     return [documentsDirectory stringByAppendingPathComponent:fileName];
 * }
 *
 * - (NSString *)writeAndReadWithMultipleNSFileHandles
 * {
 *     NSString *text = @"Text that is not protected.";
 *     NSData *fileData = [text dataUsingEncoding:NSUTF8StringEncoding];
 *
 *     NSString* filePath = [self documentsFolderPathForFileNamed:@"MyFile.txt"]
 *
 *     BOOL fileCreated = [[NSFileManager defaultManager] createFileAtPath:filePath
 *                                                        contents:fileData
 *                                                        attributes:nil];
 *
 *     // get a filehandle for Updating (read & write) and file descriptor
 *     NSFileHandle *nsFH = [NSFileHandle fileHandleForUpdatingAtPath:filePath];
 *     int filedesc = [nsFH fileDescriptor];
 *
 *     // get another filehandle with the existing filedescriptor and perform write operation
 *     NSFileHandle* writeFileHandle = [[NSFileHandle alloc] initWithFileDescriptor:filedesc closeOnDealloc:YES];
 *     [writeFileHandle writeData:testNSData];
 *     [writeFileHandle synchronizeFile];
 *     [writeFileHandle closeFile];
 *
 *     // get a filehandle for Reading
 *     NSFileHandle* readFileHandle = [NSFileHandle fileHandleForReadingAtPath:filePath];
 *     NSData* resData = [readFileHandle readDataToEndOfFile];
 *
 *     NSString *myString = [[NSString alloc] initWithData:resData encoding:NSUTF8StringEncoding];
 *
 *     return myString;
 * }
 *
 * - (NSString *)writeAndReadWithMultipleGDFileHandles
 * {
 *     NSString *text = @"Text that is to be protected by GD SDK.";
 *     NSData *fileData = [text dataUsingEncoding:NSUTF8StringEncoding];
 *
 *     NSString* filePath = [self documentsFolderPathForFileNamed:@"MyFile.txt"]
 *
 *     // Following uses GDFileManager instead of NSFileManager.
 *     BOOL fileCreated = [[GDFileManager defaultManager] createFileAtPath:filePath
 *                                                        contents:fileData
 *                                                        attributes:nil];
 *
 *     // Following uses GDFileHandle instead of NSFileHandle.
 *     // get a filehandle for Updating (read & write) and file descriptor
 *     GDFileHandle *gdFH = [GDFileHandle fileHandleForUpdatingAtPath:filePath];
 *     int filedesc = [gdFH fileDescriptor];
 *
 *     // Following uses GDFileHandle instead of NSFileHandle.
 *     // get another filehandle with the existing filedescriptor and perform write operation
 *     GDFileHandle* writeFileHandle = [[GDFileHandle alloc] initWithFileDescriptor:filedesc closeOnDealloc:YES];
 *     [writeFileHandle writeData:testNSData];
 *     [writeFileHandle synchronizeFile];
 *     [writeFileHandle closeFile];
 *
 *     // Following uses GDFileHandle instead of NSFileHandle.
 *     // get a filehandle for Reading
 *     GDFileHandle* readFileHandle = [GDFileHandle fileHandleForReadingAtPath:filePath];
 *     NSData* resData = [readFileHandle readDataToEndOfFile];
 *
 *     NSString *myString = [[NSString alloc] initWithData:resData encoding:NSUTF8StringEncoding];
 *
 *     return myString;
 * }
* \endcode
*/
@interface GDFileHandle : NSFileHandle

- (NSData *)readDataToEndOfFile;
- (NSData *)readDataOfLength:(NSUInteger)length;

- (void)writeData:(NSData *)data;
- (unsigned long long)seekToEndOfFile;
- (void)seekToFileOffset:(unsigned long long)offset;
- (void)truncateFileAtOffset:(unsigned long long)offset;
- (void)synchronizeFile;
- (void)closeFile;

- (instancetype)initWithFileDescriptor:(int)fd closeOnDealloc:(BOOL)closeopt;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

+ (nullable instancetype)fileHandleForReadingAtPath:(NSString *)path;
+ (nullable instancetype)fileHandleForWritingAtPath:(NSString *)path;
+ (nullable instancetype)fileHandleForUpdatingAtPath:(NSString *)path;

+ (nullable instancetype)fileHandleForReadingFromURL:(NSURL *)url error:(NSError **)error;
+ (nullable instancetype)fileHandleForWritingToURL:(NSURL *)url error:(NSError **)error;
+ (nullable instancetype)fileHandleForUpdatingURL:(NSURL *)url error:(NSError **)error;

@property (atomic, readonly, copy) NSData *availableData;
@property (atomic, readonly) unsigned long long offsetInFile;
@property (atomic, readonly) int fileDescriptor;

// unavailable
+ (NSFileHandle *)fileHandleWithStandardInput;
+ (NSFileHandle *)fileHandleWithStandardOutput;
+ (NSFileHandle *)fileHandleWithStandardError;
+ (NSFileHandle *)fileHandleWithNullDevice;
- (void)readInBackgroundAndNotifyForModes:(nullable NSArray<NSString *> *)modes;
- (void)readInBackgroundAndNotify;
- (void)readToEndOfFileInBackgroundAndNotifyForModes:(nullable NSArray<NSString *> *)modes;
- (void)readToEndOfFileInBackgroundAndNotify;
- (void)acceptConnectionInBackgroundAndNotifyForModes:(nullable NSArray<NSString *> *)modes;
- (void)acceptConnectionInBackgroundAndNotify;
- (void)waitForDataInBackgroundAndNotifyForModes:(nullable NSArray<NSString *> *)modes;
- (void)waitForDataInBackgroundAndNotify;
//

@end

NS_ASSUME_NONNULL_END
