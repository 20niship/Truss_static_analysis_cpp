#pragma once
#include <string>
#include <iostream>

// Objective-C++のコードを含むため、Objective-Cヘッダーをインクルード
#import <Cocoa/Cocoa.h>

std::string openFileDialog() {
  // 自動解放プールの作成
  @autoreleasepool {
    NSOpenPanel* panel = [NSOpenPanel openPanel];

    // 許可するファイルの拡張子を設定
    NSArray* fileTypes = @[ @"txt" ];

    // パネル設定
    [panel setCanChooseFiles:YES];         // ファイル選択を許可
    [panel setCanChooseDirectories:NO];    // ディレクトリ選択を許可しない
    [panel setAllowsMultipleSelection:NO]; // 複数ファイル選択を許可しない
    [panel setAllowedFileTypes:fileTypes]; // 許可されるファイルの種類
    [panel setAllowsOtherFileTypes:YES];   // すべてのファイルも許可

    // ユーザーが「開く」を押したかを確認
    if([panel runModal] == NSModalResponseOK) {
      NSURL* fileURL = [[panel URLs] objectAtIndex:0];
      return std::string([[fileURL path] UTF8String]);
    }
  }
  return "";
}

