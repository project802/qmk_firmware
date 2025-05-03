#include "quantum.h"
#include "print.h"

#define PRESS_MAX_MS    (2 * 1000)
#define WAIT_MAX_MS     (60 * 1000)
#define INTERVAL_MIN_MS (100)

static deferred_token jiggler_token = INVALID_DEFERRED_TOKEN;

uint32_t jiggler_callback( uint32_t trigger_time, void *cb_arg )
{
    typedef enum {
        JIGGLER_STATE_IDLE,
        JIGGLER_STATE_PRESSED,
    } eJigglerState;

    static eJigglerState state = JIGGLER_STATE_IDLE;
    static report_mouse_t report = { 0 };
    
    // rand() returns an int but since we are looking for a positive
    // time interval only, cast it to unsigned
    unsigned int retVal = (unsigned int) rand();
    unsigned int randShift = 0;
    
    do
    {
        randShift = ((unsigned int) rand()) & 0b111;
    }
    while( randShift == 0 || randShift > 4);
    

    uprintf( "jiggler_callback enter: state=%u retVal=0x%X randShift=%u\n", state, retVal, randShift );

    switch( state )
    {
        case JIGGLER_STATE_IDLE:
            report.buttons = MOUSE_BTN8;
            state = JIGGLER_STATE_PRESSED;
            while( retVal > PRESS_MAX_MS ) retVal = retVal >> randShift;
            break;
        
        case JIGGLER_STATE_PRESSED:
            report.buttons = 0;
            state = JIGGLER_STATE_IDLE;
            while( retVal > WAIT_MAX_MS ) retVal = retVal >> randShift;
            break;
            
        default:
            state = JIGGLER_STATE_IDLE;
            break;
    }

    host_mouse_send( &report );

    if( retVal < INTERVAL_MIN_MS ) retVal = INTERVAL_MIN_MS;
    
    uprintf( "jiggler_callback exit: state=%u retVal=%u\n", state, retVal );
    
    return (uint32_t) retVal;
}

void keyboard_post_init_user( void )
{
    jiggler_token = defer_exec( 1500, jiggler_callback, NULL );
}
