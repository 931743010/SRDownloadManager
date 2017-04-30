//
//  SRDownloadManager.h
//  SRDownloadManager
//
//  Created by 郭伟林 on 17/1/10.
//  Copyright © 2017年 SR. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SRDownloadModel.h"

typedef NS_ENUM(NSInteger, SRWaitingDownloadQueueMode) {
    SRWaitingDownloadQueueModeFIFO,
    SRWaitingDownloadQueueModeFILO
};

@interface SRDownloadManager : NSObject

/**
 The directory where the downloaded files are saved, default is .../Library/Caches/SRDownloadManager if not setted.
 */
@property (nonatomic, copy) NSString *downloadedFilesDirectory;

/**
 The count of max concurrent downloads, default is -1 which means no limit.
 */
@property (nonatomic, assign) NSInteger maxConcurrentDownloadCount;

/**
 The mode of waiting for download queue, default is FIFO.
 */
@property (nonatomic, assign) SRWaitingDownloadQueueMode waitingDownloadQueueMode;

+ (instancetype)sharedManager;

/**
 Starts a download action with URL and download state, progress, completion callback block.

 @param URL        The URL of the file which to be downloaded.
 @param state      A block object to be executed when the download state changed.
 @param progress   A block object to be executed when the download progress changed.
 @param completion A block object to be executed when the download completion.
 */
- (void)downloadFileOfURL:(NSURL *)URL
                    state:(void (^)(SRDownloadState state))state
                 progress:(void (^)(NSInteger receivedSize, NSInteger expectedSize, CGFloat progress))progress
               completion:(void (^)(BOOL success, NSString *filePath, NSError *error))completion;

- (BOOL)isDownloadCompletedOfURL:(NSURL *)URL;

#pragma mark - Downloads

- (void)suspendDownloadOfURL:(NSURL *)URL;
- (void)suspendAllDownloads;

- (void)resumeDownloadOfURL:(NSURL *)URL;
- (void)resumeAllDownloads;

- (void)cancelDownloadOfURL:(NSURL *)URL;
- (void)cancelAllDownloads;

#pragma mark - Files

- (NSString *)fileFullPathOfURL:(NSURL *)URL;

- (CGFloat)fileHasDownloadedProgressOfURL:(NSURL *)URL;

- (void)deleteFileOfURL:(NSURL *)URL;
- (void)deleteAllFiles;

@end
