
#import "AppDelegate.h"
#import <AppKit/AppKit.h>

#import "MainWindowController.h"

@interface AppDelegate()
@property (assign) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

- (void) applicationDidFinishLaunching: (NSNotification *) notification {
    MainWindowController* mainWindowController = [[MainWindowController alloc] initWithWindowNibName:@"MainWindowController"];
    
    [mainWindowController showWindow:nil];
    [mainWindowController.window setTitle:@"This is a test"];
    if (mainWindowController.window.delegate == mainWindowController) {
        NSLog(@"This is a test");
        
        [mainWindowController.window setBackgroundColor:[NSColor blackColor]];
    }
}

- (void) applicationWillTerminate: (NSNotification *) notification {
    NSLog(@"This is a test");
}

@end
