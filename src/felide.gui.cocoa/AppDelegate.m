
#import "AppDelegate.h"
#import <AppKit/AppKit.h>

#import "MainWindowViewController.h"

@interface AppDelegate()
@property (assign) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

- (void) applicationDidFinishLaunching: (NSNotification *) notification {
    MainWindowViewController* mainWindowController = [[MainWindowViewController alloc] initWithWindowNibName:@"MainWindowViewController"];
    
    [mainWindowController showWindow:nil];
    [mainWindowController.window setTitle:@"This is a test"];
    if (mainWindowController.window.delegate == mainWindowController) {
        NSLog(@"This is a test");
    }
}

- (void) applicationWillTerminate: (NSNotification *) notification {
    NSLog(@"This is a test");
}

@end
