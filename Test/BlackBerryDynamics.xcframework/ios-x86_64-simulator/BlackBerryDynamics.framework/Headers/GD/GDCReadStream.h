/*
 * (c) 2017 BlackBerry Limited. All rights reserved.
 */

#pragma once

#import <Foundation/Foundation.h>

/** NSInputStream subclass for reading files that are in the secure store.
 * 
 * This class is a subclass of the native <tt>NSInputStream</tt> class, for
 * access to the BlackBerry Dynamics secure file system.
 *
 * @see \ss_filesystem_link
 * @see \link GDFileHandle \endlink
 *
 * <h2>Programming Interface</h2>
 * This class supports the <tt>read</tt> and <tt>hasBytesAvailable</tt> member
 * functions of <tt>NSInputStream</tt>. This class doesn't support
 * <tt>getBuffer</tt>, which will always return <tt>NO</tt>. This class also
 * doesn't support <tt>scheduleInRunLoop</tt> nor <tt>removeFromRunLoop</tt>.
 * Support for run loops isn't required because the file data can be read
 * immediately.
 *
 * This documentation includes only additional operations provided by
 * GDCReadStream that aren't part of <tt>NSInputStream</tt>.
 *
 * \par Notes on use of the read function
 * The <tt>read</tt> function in this class will work best when the supplied
 * buffer is a multiple of 16 bytes in length. The <tt>maxLength</tt> parameter
 * should reflect the size of the buffer, and not the amount of data remaining
 * to be read from the file. To read a particular number of bytes, <em>B</em>,
 * supply a buffer whose size is <em>B </em>rounded up to the next multiple of
 * 16.\n
 * The return value of the <tt>read</tt> function must always be checked by the
 * application. It mustn't be assumed that a file has been completely read into
 * a buffer, even if the buffer is large enough to accomodate the whole file.
 *
 * \error_param_intro{this class}
 * 
 * @see <a
 *          href="https://developer.apple.com/reference/foundation/nsinputstream"
 *          target="_blank"
 *      >NSInputStream class reference</a> on the apple.com developer website.
 * @see \ref GDCWriteStream
 */
@interface GDCReadStream : NSInputStream <NSStreamDelegate>

/** Constructor that opens a file in the secure store, for reading.
 * 
 * Call this constructor to open a file in the secure store for reading. Files
 * in the secure store are encrypted on the device; this function provides
 * access to decrypted data.
 *
 * Note. This constructor is used by the
 * \ss_class_link{GDFileManager,getReadStream:error:,getReadStream:}
 * \ss_function in the \ss_filesystem_link class.
 *
 * @param filePath <tt>NSString</tt> containing the path, within the secure
 *                 store, of the file to be opened.
 *
 * \error_param
 *
 * @return \ss_null if the file could not be opened.
 */
- (instancetype) initWithFile:(NSString*)filePath error:(NSError**)error;

/** Constructor that opens a file in the secure store, for reading.
 * 
 * Calling this constructor is equivalent to calling the
 * \ref initWithFile:error: constructor, above, and specifying \ss_null as the
 * <tt>error</tt> parameter.
 */
- (instancetype) initWithFile:(NSString*)filePath;

/** Seek in an open file in the secure file system.
 * 
 * Call this function to move the file pointer to a specific offset from the
 * start of the stream.
 *
 * @param offset Required offset, expressed as a number of bytes from the start
 *               of the file. Zero means the start of the file.
 *
 * @return \ss_true if the file pointer was moved to the required offset.
 * @return \ss_false Otherwise.
 */
- (BOOL)seekToFileOffset:(unsigned long long)offset;


/** Get the last error.
 * 
 * Call this function to get the last error associated with the open stream.
 *
 * @return Reference to an <tt>NSError</tt> object that describes the error.
 * 
 * \if iOS @see \ref gdfilemanagererrordomain \endif
 */
- (NSError*) streamError;

@end
