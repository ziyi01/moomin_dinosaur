/* This function is called repetitively from the main program */
void labwork( void )
{
    while (timeoutcount <= 10) {
    // Möjligtvist olagligt för checkbutton är inuti loopen,
    // men det runnas i varje loop och verkar inte vara något delay?
    checkButton();
    if(IFS(0) & 0x100) {
      IFS(0) = IFS(0) & ~0x100; // Reset the flag
      timeoutcount++;
    } 
  } // Check if interrupted, flag status changed or not
  timeoutcount = 0;
  IFS(0) = IFS(0) & ~0x100;

  time2string( textstring, mytime );
  // Takes a while for the display from buttons to update as this is run every 10 time-outs
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  tickLED(&counter); // It starts at 0x5957 so can't directly use mytime - 0x5957
  display_image(96, icon);
}
