/*
 * (c) 2017 BlackBerry Limited. All rights reserved.
 */

#pragma once

#import <Foundation/Foundation.h>

/** NSOutputStream subclass for writing files in the secure store.
 * 
 * This class is a subclass of the native <tt>NSInputStream</tt> class, for
 * access to the BlackBerry Dynamics secure file system.
 *
 * @see \ss_filesystem_link
 * @see \link GDFileHandle \endlink
 * 
 * <h2>Programming Interface</h2>
 * The class supports the <tt>write</tt> and <tt>hasSpaceAvailable</tt> member
 * functions of <tt>NSOutputStream</tt>. The subclass doesn't support
 * <tt>scheduleInRunLoop</tt> nor <tt>removeFromRunLoop</tt>. Support for run
 * loops isn't required because the file data can be written immediately.
 *
 * This documentation includes only additional operations provided by
 * GDCWriteStream that are not part of <tt>NSOutputStream</tt>.
 *
 * \error_param_intro{this class}
 *
 * @see <a
 *          href="https://developer.apple.com/reference/foundation/nsoutputstream?language=objc"
 *          target="_blank"
 *      >NSOutputStream class reference</a> on the apple.com developer website.
 * @see \ref GDCReadStream
 */
@interface GDCWriteStream : NSOutputStream <NSStreamDelegate>

/** Constructor that opens or creates a file in the secure store, for writing.
 * 
 * Call this constructor to create a new file in the secure store, or to open an
 * existing file for writing. Files in the secure store are encrypted on the
 * device; data written to the stream returned by this function will be
 * encrypted, transparently to the application.
 *
 * If a file already exists at the specified path, the file can either be
 * appended to, or overwritten.
 *
 * Note. This constructor is used by the
 * \ss_class_link{GDFileManager,getWriteStream:appendmode:error:,getWriteStream:}
 * \ss_function in the \ss_filesystem_link class.
 *
 * @param filePath <tt>NSString</tt> containing the path, within the secure
 *                 store, of the file to be opened.
 *
 * @param shouldAppend Selects the action to take if a file already exists at
 *                     the path: <tt>YES</tt> to append to the file, or
 *                     <tt>NO</tt> to overwrite.
 *
 * \error_param
 *
 * @return \ss_null if the file couldn't be opened.
 */
- (instancetype)initWithFile:(NSString*)filePath append:(BOOL) shouldAppend error:(NSError**)error;

/** Constructor that opens or creates a file in the secure store, for writing.
 * 
 * Calling this constructor is equivalent to calling the
 * \ref initWithFile:append:error: constructor, above, and specifying \ss_null
 * as the <tt>error</tt> parameter.
 */
- (instancetype)initWithFile:(NSString*)filePath append:(BOOL) shouldAppend;

/** Get the last error.
 * 
 * Call this function to get the last error associated with the open stream.
 *
 * @return Reference to an <tt>NSError</tt> object that describes the error.
 * \if iOS @see \ref gdfilemanagererrordomain \endif
 */
- (NSError*) streamError;

@end
