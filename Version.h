#ifndef VERSION_H
#define VERSION_H


#define APPLICATION_TITLE     "WPCEdit"
#define APPLICATION_COPYRIGHT "Copyright (c) 2011"
#define APPLICATION_AUTHOR    "Garrett Lee, mrglee@yahoo.com"

#define APPLICATION_VERSION   2.0
//
// Revision History
// ----------------
//
// v1.0  Initial build for release.  March 15, 2004
//
// v1.1  Fix bug where a divide-by-zero error occurs when the window is sized
//       super small.  This was a bug in the HexEditor free source code.
//
// v1.2  Considering making a general release that is not customized for each user
//       but they still have to email me for registeration code.  In preperation for
//       this adding lots of 'Confuse' code to try to deter somebody from tracing
//       or debugging the code to try to figure out what is going on.
//       
//       Additionally for v1.2 added a nag screen when the user goes to look at DMD
//       data.  This is a one-time nag.
//
//       Additionally fixed the About-box title, it was saying "About HexEditor" it 
//       now says "About WPCEdit".
//
// v1.2b Custom version for user which only decodes DMD data for WhoDunnit.
//
// v1.3  Fixed the problem where some DMD images weren't being decoded properly.
//       The problem was just that image type 0x05 wasn't being done right.  It
//       was a simple fix.
//
// v1.3rs  Special version that only does Road Show for a rgp user
//
//
// v1.5  Public release, all lock-code stuff inhibited. February 5, 2005
//
// Post-v1.5: Making source code public, clearing out the anal-retentive security
// info from the source files but didn't check if it will compile.  Source code had
// some email addresses of individual users who received the app, early on, and the
// s/w was designed to ONLY work on their computers by way of a disk-id check and
// md5 hashing..
//
// v2.0  Resurrecting wpcEdit, cleaned up the source a bit, removed obfuscation.
//       Cleaned up function calls, put in Font Dialog!!  Dumps font tables from
//       all WPC Roms.
//






#endif // end #ifndef VERSION_H #define VERSION_H file wrapper