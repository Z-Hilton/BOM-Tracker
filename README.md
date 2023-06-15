# BOM-Tracker
A guide to how I built the ultimate DIY Book of Mormon Progress Tracker. It is designed to help with reading goals and make tracking your progress through the Book of Mormon just a bit more fun.

## Background
I wanted something that would essentially function like a glorified bookmark, keeping track of stats, times, progress, averages, etc. I thought about making an app for a smartphone, but decided that another app that I eventually forget about wouldn't be as exciting as a physical piece of hardware that can sit on my nightstand as a constant reminder that I only get to click its buttons if I have read :) (Also, I try to avoid being on my phone before going to bed). Thus the idea to use a microcontroller was born. I thought abut using a Teensy 3.2 since I already have one, but decided that for reproducability's sake I would use the much cheaper $4 Raspberry Pi Pico. 

## Functionality
* *Time tracking:* You can start, pause and stop a timer to track your time spent reading. The spent time will be displayed briefly on the OLED screen before returning to the normal UI, then after 7 times, it will calculate your weekly average and display that to the screen, allowing you to see if you met your goal. 
* *Chapter progress tracking:* You can increment and decrement which chapter you're on and update the display accordingly. Then it will do the math to show the total progress and display it on the OLED screen as a percentage or progress bar.
* *User interface:* It has a simple UI consisting of a few buttons for selecting chapters and start/pause/stopping the timer. The OLED display will provide feedback on the device's status and progress. An external LED shows the current timer status (started = on, paused = blinking, stopped = off). 

## Bill of Materials
Warning: *the following cost analysis assumes you have access to an FDM and Resin 3D printer. These are based on rates I found locally at BYU* 

I spent about $25 on this project, and ended up with lots of extra parts. I also had to iterte a few times on my designs for the housing and the keycaps before they worked well. In theory you could build this in under $17.30:
Item # | Description | Quantity | Cost Per Item | Cost
---|---|---|---|---
1 | [Raspberry Pi Pico](https://www.raspberrypi.com/products/raspberry-pi-pico/) | 1 | $4.00 | $4.00
2 | [Micro USB Cable](https://www.amazon.com/CableWholesale-10-Feet-Micro-Cable-10U2-03110BK/dp/B002I8MUJG/ref=sr_1_2_mod_primary_new?crid=1UUFJBJONUO7B&keywords=micro+usb&qid=1685855258&refinements=p_36%3A-200&rnid=386442011&sbo=RZvfv%2F%2FHxDF%2BO5021pAnSA%3D%3D&sprefix=micro+usb%2Caps%2C154&sr=8-2) | 1 | $2.00 | $2.00
3 | [PLA filament](https://www.amazon.com/OVERTURE-Filament-Consumables-Dimensional-Accuracy/dp/B07PGY2JP1/ref=sxin_16_pa_sp_search_thematic_sspa?content-id=amzn1.sym.9efcc700-d635-445c-9d53-884ea58d759c%3Aamzn1.sym.9efcc700-d635-445c-9d53-884ea58d759c&crid=1JCQ45ZD0F87J&cv_ct_cx=pla+filament+1kg&keywords=pla+filament+1kg&pd_rd_i=B07PGY2JP1&pd_rd_r=9764d323-c8f6-470f-9c73-72e51a698ef1&pd_rd_w=tOOPV&pd_rd_wg=3bLec&pf_rd_p=9efcc700-d635-445c-9d53-884ea58d759c&pf_rd_r=MXC1Q3EGBBFNR0CG4NV5&qid=1685855370&sbo=RZvfv%2F%2FHxDF%2BO5021pAnSA%3D%3D&sprefix=pla+filament+1kg%2Caps%2C168&sr=1-1-2b34d040-5c83-4b7f-ba01-15975dfb8828-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzUzMzN0ZGS0JRQjdaJmVuY3J5cHRlZElkPUEwMzkzMjM4M0VVRTBROTg2OTNQRiZlbmNyeXB0ZWRBZElkPUEwMTE2NjI0MVpOR0o1RjFWMThLNyZ3aWRnZXROYW1lPXNwX3NlYXJjaF90aGVtYXRpYyZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=) | 50 grams | $20/kg | $1.00
4 | LED (any color) | 1 | $0.10 | $0.10
5 | [Keyboard Switches](https://www.amazon.com/Switches-Replaceable-Equivalent-Keyswitch-Mechanical/dp/B09WHDJJBT/ref=sr_1_2?crid=35BZ7OAAITHQ3&keywords=outemu+keyboard+switches+black+10+pack&qid=1685855507&s=industrial&sprefix=outemu+keyboard+switches+black+10+pack%2Cindustrial%2C144&sr=1-2) | 3 | $10/10pc | $3.00
6 | Resin Keycaps | 3 | $0.25/ml | $1.20
7 | [SSH1106 1.3" OLED](https://www.amazon.com/Teyleten-Robot-Display-Raspberry-Microcontroller/dp/B08J1D212N/ref=sr_1_4?crid=25FMTKZWHS90C&keywords=1.3%22+oled&qid=1685853207&sprefix=1.3+oled%2Caps%2C143&sr=8-4) | 1 | $12/2pc | $6.00

## Build/Pictures
[Here is a link](https://www.thingiverse.com/thing:4816077) to the model I started with and modified to suit the needs of my 3 buttons and OLED screen. They are relatively simple edits and can be done very quickly in Fusion 360. I did not modify the bottom half, and the changes I made to the top half are reflected in the .stp file I exported and included above. 


<img src="https://github.com/Z-Hilton/BOM-Tracker/blob/main/Images/on.jpg" width="200" /> <img src="https://github.com/Z-Hilton/BOM-Tracker/blob/main/Images/off_time.jpg" width = "200"> <img src="https://github.com/Z-Hilton/BOM-Tracker/blob/main/Images/open.jpg" width = "200"> <img src="https://github.com/Z-Hilton/BOM-Tracker/blob/main/Images/open_bottom.jpg" width = "355"> <img src="https://github.com/Z-Hilton/BOM-Tracker/blob/main/Images/open_top.jpg" width = "355">

## Video
<a href="https://www.youtube.com/watch?v=dQw4w9WgXcQ"> <img src="https://github.com/Z-Hilton/BOM-Tracker/blob/main/Images/on.jpg" alt="Image" width="500"> </a>



