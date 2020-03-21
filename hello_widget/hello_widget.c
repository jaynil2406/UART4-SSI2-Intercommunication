#include <stdbool.h>
#include <stdint.h>
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "grlib/grlib.h"
#include "grlib/widget.h"
#include "grlib/canvas.h"
#include "grlib/pushbutton.h"
//#include "inc/hw_ints.h"
#include "driverlib/uart.h"
#include "drivers/frame.h"
#include "drivers/kentec320x240x16_ssd2119.h"
#include "drivers/pinout.h"
#include "drivers/touch.h"
#include "utils/uartstdio.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "tm4c129xnczad.h"
#include "driverlib/interrupt.h"

#define GREEN_LED  GPIO_PIN_7
#define BLUE_LED  GPIO_PIN_4
#define RED_LED  GPIO_PIN_5
#define NEW_LED GPIO_PIN_6
uint32_t value_of =0;
//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Hello using Widgets (hello_widget)</h1>
//!
//! A very simple ``hello world'' example written using the TivaWare Graphics
//! Library widgets.  It displays a button which, when pressed, toggles
//! display of the words ``Hello World!'' on the screen.  This may be used as
//! a starting point for more complex widget-based applications.
//
//*****************************************************************************

//*****************************************************************************
//
// Forward reference to various widget structures.
//
//*****************************************************************************
extern tCanvasWidget g_sBackground;
extern tPushButtonWidget g_sPushBtn,g_sCharIncBtn,g_sCharIncBtn;
extern tPushButtonWidget g_sCharDecBtn,g_sNumIncBtn,g_CheckcBtn;
//*****************************************************************************
//
// Forward reference to the button press handler.
//
//*****************************************************************************
void OnButtonPress(tWidget *psWidget);
void OnButtonPress1(tWidget *psWidget);
void OnButtonPress2(tWidget *psWidget);
void OnButtonPress3(tWidget *psWidget);


//*****************************************************************************
//
// The canvas widget acting as the background to the display.
//
//*****************************************************************************
Canvas(g_sBackground, WIDGET_ROOT, 0, &g_sPushBtn,
       &g_sKentec320x240x16_SSD2119, 10, 25, 300, (240 - 25 -10),
       CANVAS_STYLE_FILL, ClrBlack, 0, 0, 0, 0, 0, 0);

//*****************************************************************************
//
// The button used to hide or display the "Hello World" message.
//
//*****************************************************************************
RectangularButton(g_sPushBtn, &g_sBackground, &g_sCharDecBtn, 0,
                  &g_sKentec320x240x16_SSD2119, 60, 40, 200, 40,
                  (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT |
                   PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
                   ClrWhite, ClrBlue, ClrGold, ClrBlack,
                   g_psFontCmss14b, "", 0, 0, 0, 0, OnButtonPress);
RectangularButton(g_sCharDecBtn, &g_sBackground,&g_sCharIncBtn, 0,
                  &g_sKentec320x240x16_SSD2119, 60, 90, 200, 40,
                                   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT |
                                    PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
                                    ClrRed, ClrBlack, ClrYellow, ClrWhite,
                                    g_psFontCmss14b, "RED LED TOUCH", 0, 0, 0, 0, OnButtonPress1);
RectangularButton(g_sCharIncBtn, &g_sBackground,&g_sNumIncBtn, 0,
                  &g_sKentec320x240x16_SSD2119, 60, 140, 200, 40,
                                   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT |
                                    PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
                                    ClrGreen, ClrBlack, ClrYellow, ClrWhite,
                                    g_psFontCmss14b, "GREEN LED TOUCH", 0, 0, 0, 0, OnButtonPress2);
RectangularButton(g_sNumIncBtn, &g_sBackground,0, 0,
                  &g_sKentec320x240x16_SSD2119, 60, 190, 200, 40,
                                   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT |
                                    PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
                                    ClrBlue, ClrBlack, ClrYellow, ClrWhite,
                                    g_psFontCmss14b, "BLUE LED TOUCH", 0, 0, 0, 0, OnButtonPress3);
//*****************************************************************************
//
// The canvas widget used to display the "Hello!" string.  Note that this
// is NOT hooked into the active widget tree (by making it a child of the
// g_sPushBtn widget above) yet since we do not want the widget to be displayed
// until the button is pressed.
//
//*****************************************************************************
Canvas(g_sHello, &g_sPushBtn, 0, 0,
       &g_sKentec320x240x16_SSD2119, 0, 1, 1, 1,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_TEXT),
       ClrBlack, 0, ClrWhite, g_psFontCm40, "", 0, 0);

//*****************************************************************************
//
// A global we use to keep track of whether or not the "Hello" widget is
// currently visible.
//
//*****************************************************************************
bool g_bHelloVisible = false;

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

//*****************************************************************************
//
// This function is called by the graphics library widget manager in the
// context of WidgetMessageQueueProcess whenever the user releases the
// "Press Me!" button.  We use this notification to display or hide the
// "Hello!" widget.
//
// This is actually a rather inefficient way to accomplish this but it's
// a good example of how to add and remove widgets dynamically.  In
// normal circumstances, you would likely leave the g_sHello widget
// linked into the tree and merely add or remove the text by changing
// its style then repainting.
//
// If using this dynamic add/remove strategy, another useful optimization
// is to use a black canvas widget that covers the same area of the screen
// as the widgets that you will be adding and removing.  If this is the used
// as the point in the tree where the subtree is added or removed, you can
// repaint just the desired area by repainting the black canvas rather than
// repainting the whole tree.
//
//*****************************************************************************
void
OnButtonPress(tWidget *psWidget)
{

}
void
OnButtonPress1(tWidget *psWidget)
{
    UART5_DR_R = 'R';
    g_bHelloVisible = !g_bHelloVisible;


        //
        // Add the Hello widget to the tree as a child of the push
        // button.  We could add it elsewhere but this seems as good a
        // place as any.  It also means we can repaint from g_sPushBtn and
        // this will paint both the button and the welcome message.
        //
        WidgetAdd((tWidget *)&g_sCharDecBtn, (tWidget *)&g_sHello);

        //
        // Change the button text to indicate the new function.
        //
       // PushButtonTextSet(&g_sPushBtn, "Hide Welcome");
        GPIOPinWrite(GPIO_PORTQ_BASE, GREEN_LED,0);
                                                              GPIOPinWrite(GPIO_PORTN_BASE, RED_LED, RED_LED);
                                                              GPIOPinWrite(GPIO_PORTQ_BASE, NEW_LED,0);
                                                              GPIOPinWrite(GPIO_PORTQ_BASE, BLUE_LED,0);
        //
        // Repaint the pushbutton and all widgets beneath it (in this case,
        // the welcome message).
        //
        WidgetPaint((tWidget *)&g_sCharDecBtn);


        //
        // Remove the Hello widget from the tree.
        //
        WidgetRemove((tWidget *)&g_sHello);

        //
        // Change the button text to indicate the new function.
        //
        PushButtonTextSet(&g_sPushBtn, "RED LED TOUCH");

        //
        // Repaint the widget tree to remove the Hello widget from the
        // display.  This is rather inefficient but saves having to use
        // additional widgets to overpaint the area of the Hello text (since
        // disabling a widget does not automatically erase whatever it
        // previously displayed on the screen).
        //
        WidgetPaint(WIDGET_ROOT);

}
void
OnButtonPress2(tWidget *psWidget)
{
    UART5_DR_R = 'G';
    g_bHelloVisible = !g_bHelloVisible;


        //
        // Add the Hello widget to the tree as a child of the push
        // button.  We could add it elsewhere but this seems as good a
        // place as any.  It also means we can repaint from g_sPushBtn and
        // this will paint both the button and the welcome message.
        //
        WidgetAdd((tWidget *)&g_sCharIncBtn, (tWidget *)&g_sHello);

        //
        // Change the button text to indicate the new function.
        //
       // PushButtonTextSet(&g_sPushBtn, "Hide Welcome");
        GPIOPinWrite(GPIO_PORTQ_BASE, GREEN_LED,GREEN_LED);
                                                              GPIOPinWrite(GPIO_PORTN_BASE, RED_LED, 0x0);
                                                              GPIOPinWrite(GPIO_PORTQ_BASE, NEW_LED,0);
                                                              GPIOPinWrite(GPIO_PORTQ_BASE, BLUE_LED,0);
        //
        // Repaint the pushbutton and all widgets beneath it (in this case,
        // the welcome message).
        //
        WidgetPaint((tWidget *)&g_sCharIncBtn);

        //
        // Remove the Hello widget from the tree.
        //
        WidgetRemove((tWidget *)&g_sHello);

        //
        // Change the button text to indicate the new function.
        //
        PushButtonTextSet(&g_sPushBtn, "GREEN LED TOUCH");

        //
        // Repaint the widget tree to remove the Hello widget from the
        // display.  This is rather inefficient but saves having to use
        // additional widgets to overpaint the area of the Hello text (since
        // disabling a widget does not automatically erase whatever it
        // previously displayed on the screen).
        //
        WidgetPaint(WIDGET_ROOT);

}
void
OnButtonPress3(tWidget *psWidget)
{
    UART5_DR_R = 'B';
    g_bHelloVisible = !g_bHelloVisible;



            //
            // Add the Hello widget to the tree as a child of the push
            // button.  We could add it elsewhere but this seems as good a
            // place as any.  It also means we can repaint from g_sPushBtn and
            // this will paint both the button and the welcome message.
            //
            WidgetAdd((tWidget *)&g_sPushBtn, (tWidget *)&g_sHello);

            //
            // Change the button text to indicate the new function.
            //
            //PushButtonTextSet(&g_sPushBtn, "Hide Welcome");
            GPIOPinWrite(GPIO_PORTQ_BASE, GREEN_LED,0);
                                                    GPIOPinWrite(GPIO_PORTN_BASE, RED_LED, 0x0);
                                                    GPIOPinWrite(GPIO_PORTQ_BASE, NEW_LED,0);
                                                    GPIOPinWrite(GPIO_PORTQ_BASE, BLUE_LED,BLUE_LED);
            //
            // Repaint the pushbutton and all widgets beneath it (in this case,
            // the welcome message).
            //
            WidgetPaint((tWidget *)&g_sPushBtn);



            //
            // Remove the Hello widget from the tree.
            //
            WidgetRemove((tWidget *)&g_sHello);

            //
            // Change the button text to indicate the new function.
            //
            PushButtonTextSet(&g_sPushBtn, "BLUE LED TOUCH");

            //
            // Repaint the widget tree to remove the Hello widget from the
            // display.  This is rather inefficient but saves having to use
            // additional widgets to overpaint the area of the Hello text (since
            // disabling a widget does not automatically erase whatever it
            // previously displayed on the screen).
            //
            WidgetPaint(WIDGET_ROOT);

}
void
UART0IntHandler(void)
{
    uint32_t ui32Status;

    //
    // Get the interrrupt status.
    //
    ui32Status = ROM_UARTIntStatus(UART0_BASE, true);

    //
    // Clear the asserted interrupts.
    //
    ROM_UARTIntClear(UART0_BASE, ui32Status);

    //
    // Loop while there are characters in the receive FIFO.
    //
    while(ROM_UARTCharsAvail(UART0_BASE))
    {
        //
        // Read the next character from UART0 and sent it to UART3.
        //
     //   value_of = UARTCharGet(UART0_BASE);
        UARTCharPutNonBlocking(UART0_BASE, UARTCharGet(UART0_BASE));
        //ROM_UARTCharPutNonBlocking(UART0_BASE,
                                         // UARTCharGetNonBlocking(UART0_BASE));

    }
}
void
ConfigureUART(void)
{
     uint32_t ui32SysClock;

    //
    // Run from the PLL at 120 MHz.
    //
    ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                           SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
                                           SYSCTL_CFG_VCO_480), 40000000);

    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PH6_U5RX);
    ROM_GPIOPinConfigure(GPIO_PH7_U5TX);
    ROM_GPIOPinTypeUART(GPIO_PORTH_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
   // ROM_UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    ROM_UARTConfigSetExpClk(UART5_BASE, ui32SysClock, 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));

}


//*****************************************************************************
//
// Print "Hello World!" to the display on the Intelligent Display Module.
//
//*****************************************************************************
int
main(void)
{
    tContext sContext;
    uint32_t ui32SysClock;

    //
    // Run from the PLL at 120 MHz.
    //
    ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                           SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
                                           SYSCTL_CFG_VCO_480), 40000000);



    //
    // Configure the device pins.
    //
    PinoutSet();

    //
    // Initialize the display driver.
    //
    Kentec320x240x16_SSD2119Init(ui32SysClock);

    //
    // Initialize the graphics context.
    //
    GrContextInit(&sContext, &g_sKentec320x240x16_SSD2119);

    //
    // Draw the application frame.
    //
    FrameDraw(&sContext, "hello-widget");

    //
    // Initialize the touch screen driver.
    //
    TouchScreenInit(ui32SysClock);

    //
    // Set the touch screen event handler.
    //
    TouchScreenCallbackSet(WidgetPointerMessage);

    //
    // Add the compile-time defined widgets to the widget tree.
    //
    WidgetAdd(WIDGET_ROOT, (tWidget *)&g_sBackground);
    GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GREEN_LED);//|USER_LED2));
                     GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, BLUE_LED);

                   GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, RED_LED);
    //
    // Paint the widget tree to make sure they all appear on the display.
    //
    WidgetPaint(WIDGET_ROOT);

    ConfigureUART();

   // value_of =  UART5_DR_R ;

    //
    // Loop forever, processing widget messages.
    //

    while(1)
    {
        //
        // Process any messages from or for the widgets.
        //
        WidgetMessageQueueProcess();
    }
}
