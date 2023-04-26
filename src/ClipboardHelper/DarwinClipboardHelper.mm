// ClipboardHelper.mm
#import <AppKit/AppKit.h>  // import is for obj-c only

#include "ClipboardHelper.h"

// https://developer.apple.com/documentation/appkit/nspasteboard

std::string ClipboardHelper::getString() {
  NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];
  NSString* str = [pasteboard stringForType:NSPasteboardTypeString];
  return str ? std::string([str UTF8String]) : std::string();
}

std::string ClipboardHelper::getURL() {
  NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];
  NSString* str = [pasteboard stringForType:NSPasteboardTypeURL];
  return str ? std::string([str UTF8String]) : std::string();
}

std::string ClipboardHelper::getFilePath() {
  NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];
  NSString* str = [pasteboard stringForType:NSPasteboardTypeFileURL];
  return str ? std::string([str UTF8String]) : std::string();
}

void ClipboardHelper::setString(const std::string& input) {
  NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];
  [pasteboard clearContents];
  NSString* str = [NSString stringWithUTF8String:input.c_str()];
  [pasteboard setString:str forType:NSPasteboardTypeString];
}
