
#import <Cocoa/Cocoa.h>
#import "AppDelegate.h"

int main(int argc, const char *argv[]) {
    /*
    NSArray *topLevelObjects = nil;

    NSApplication *app = [NSApplication sharedApplication];
    [[NSBundle mainBundle] loadNibNamed: @"MainMenu" owner: app topLevelObjects: &topLevelObjects];

    AppDelegate *appDelegate = [[AppDelegate alloc] init];

    [app setDelagate: appDelegate];
    [app run];

    return 0;
    */
    
    @autoreleasepool {}
    
    AppDelegate *appDelegate = [[AppDelegate alloc] init];
    [[NSApplication sharedApplication] setDelegate:appDelegate];
    
    return NSApplicationMain(argc, argv);
}
