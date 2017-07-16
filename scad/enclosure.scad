width = 53;
height = 85;
depth = 13.5;
thickness = 2;
clearance = 0.2;

lcd_pcb_width = 43;
lcd_pcb_height = 77;
lcd_pcb_depth = 1;
lcd_pcb_offset = 5;

lcd_width = 43;
lcd_height = 60.5;
lcd_depth = 2;
lcd_offset = 10; // offset from bottom of lcd pcb to lcd edge

lcd_connector_width = 36;
lcd_connector_depth = 3;
lcd_connector_height = 30;
lcd_connector_offset = 0.5; // offset from bottom of pcb to connector edge

lcd_display_width = 38;
lcd_display_height = 50;
lcd_display_offset = 7; // offset from the bottom of the lcd to the display part

lcd_hole_spacing_x = 38;

module ilI9341() {
    difference() {
        union() {
            // pcb
            cube([lcd_pcb_width, lcd_pcb_height, lcd_pcb_depth]);
            // lcd
            translate([0, lcd_offset, 1]) cube([lcd_width, lcd_height, 2]);
            // display clearance
            translate([(lcd_width - lcd_display_width)/2, lcd_offset + lcd_display_offset, 3])
                cube([lcd_display_width, lcd_display_height, 1]);
            // connector clearance
            translate([(lcd_pcb_width - lcd_connector_width)/2, lcd_connector_offset, -lcd_connector_height + 3]) cube([lcd_connector_width, lcd_connector_depth, lcd_connector_height]);
            // screw and nuts clearance
            for(i=[-1,1]) translate([lcd_pcb_width/2 - i * lcd_hole_spacing_x/2, lcd_pcb_height -2.5, 0]) {
                translate([0, 0, 1]) cylinder(d=5, h=2.5);
                translate([0, 0, -10]) cylinder(d=3, h=10, $fn=20);
            }
            for(i=[-1,1]) translate([lcd_pcb_width/2 - i * lcd_hole_spacing_x/2, 6.5, 0]) {
                translate([0, 0, 1]) cylinder(d=5, h=2.5);
                translate([0, 0, -10]) cylinder(d=3, h=10, $fn=20);
            }
        }
        // mounting holes
        for(i=[-1,1]) translate([lcd_pcb_width/2 - i * lcd_hole_spacing_x/2, lcd_pcb_height -2.5, 0]) {
            cylinder(d=3.5, h=1, $fn=20);
        }
        for(i=[-1,1]) translate([lcd_pcb_width/2 - i * lcd_hole_spacing_x/2, 6.5, 0]) cylinder(d=3.5, h=1, $fn=20);
    }

}

node_length = 48;
node_width = 30.5;
node_connector_spacing = 28;
node_connector_length = 38;

module node_mcu() {
    // pcb
    cube([node_length, node_width, 1.5]);
    // pins
    translate([3, 0, -3]) cube([node_connector_length, 2.5, 30]);
    translate([3, node_width - 2.5, -3]) cube([node_connector_length, 2.5, 30]);
    // components
    translate([0, 5.5, -3]) cube([20, 18.5, 3]);
    translate([20, 5.5, -5]) cube([node_length - 20, 18.5, 5]);
    // usb port
    translate([-10, node_width/2 - 5, -2]) cube([10,10, 2]);
}

module node_bottom_support() {
    cube([lcd_pcb_width, 5, 2]);
    translate([23, 0, 0]) cube([20, 30, 2]);
}

module node_top_support() {
    cube([lcd_pcb_width + 2, 40, 2]);
    translate([0, 0, -3.5]) cube([lcd_pcb_width, 4, 3.5]);
}

/* node_mcu(); */
/* ilI9341(); */

/* difference() { */
/*     // enclosure */
/*     cube([width, height, depth]); */
/*     // carving up the inside */
/*     translate([thickness, thickness, thickness]) */
/*         cube([width - thickness * 2, height - thickness * 2, depth]); */
/*     # translate([lcd_pcb_width + (width - lcd_pcb_width)/2, lcd_pcb_offset, 4,]) rotate([0, 180, 0]) ilI9341(); */
/*     # translate([51, 45, 10]) rotate([0, 0, 180]) node_mcu(); */
/* } */

/* difference() { */
/*     translate([5, 9, 6]) node_bottom_support(); */
/*     translate([lcd_pcb_width + (width - lcd_pcb_width)/2, lcd_pcb_offset, 4,]) rotate([0, 180, 0]) ilI9341(); */
/*     translate([51, 45, 10]) rotate([0, 0, 180]) node_mcu(); */
/* } */

/* difference() { */
/*     translate([5, 9, 11.5]) node_top_support(); */
/*     translate([lcd_pcb_width + (width - lcd_pcb_width)/2, lcd_pcb_offset, 4,]) rotate([0, 180, 0]) ilI9341(); */
/*     translate([51, 45, 10]) rotate([0, 0, 180]) node_mcu(); */
/* } */

module top_case() {
    difference() {
        union() {
            linear_extrude(height = width)
                polygon([[0, 0], [0, height], [35, 10]]);
            difference() {
                translate([40, 5, 5]) rotate([0, -90, 0]) {
                    for(i=[-1,1]) translate([lcd_pcb_width/2 - i * lcd_hole_spacing_x/2, lcd_pcb_height -2.5, 0]) {
                        cylinder(d=6.5, h=40, $fn=20);
                    }
                    for(i=[-1,1]) translate([lcd_pcb_width/2 - i * lcd_hole_spacing_x/2, 6.5, 0]) {
                        cylinder(d=6.5, h=40, $fn=20);
                    }
                }
                linear_extrude(height = width) polygon([ [0,0], [35, 10], [0, height], [50, height], [50, 0]]);
            }
        }
        translate([0, 0, thickness]) linear_extrude(height = width - thickness * 2)
            polygon([[0, 2], [0, height - 2], [33, 11]]);
        translate([40, 5, 5]) rotate([0, -90, 0]) {
            for(i=[-1,1]) {
                translate([lcd_pcb_width/2 - i * lcd_hole_spacing_x/2, lcd_pcb_height -2.5, 0])
                    cylinder(d=5.5, h=40, $fn=20);
                translate([lcd_pcb_width/2 - i * lcd_hole_spacing_x/2, 6.5, 0])
                    cylinder(d=5.5, h=40, $fn=20);
            }
        }
    }
    difference() {
    translate([40, 5, 5]) rotate([0, -90, 0]) {
        difference() {
            for(i=[-1,1]) {
                translate([lcd_pcb_width/2 - i * lcd_hole_spacing_x/2, lcd_pcb_height -2.5, 0])
                    cylinder(d=6.5, h=40, $fn=20);
                translate([lcd_pcb_width/2 - i * lcd_hole_spacing_x/2, 6.5, 0])
                    cylinder(d=6.5, h=40, $fn=20);
            }
            for(i=[-1,1]) {
                translate([lcd_pcb_width/2 - i * lcd_hole_spacing_x/2, lcd_pcb_height -2.5, 0])
                    cylinder(d=5.5, h=40, $fn=20);
                translate([lcd_pcb_width/2 - i * lcd_hole_spacing_x/2, 6.5, 0])
                    cylinder(d=5.5, h=40, $fn=20);
            }
        }
    }
    linear_extrude(height = width) polygon([ [0,0], [35, 10], [0, height], [50, height], [50, 0]]);
    }
    translate([2, 5, 5]) rotate([0, -90, 0]) {
        difference() {
            for(i=[-1,1]) {
                translate([lcd_pcb_width/2 - i * lcd_hole_spacing_x/2, lcd_pcb_height -2.5, 0])
                    cylinder(d=6.5, h=2, $fn=20);
                translate([lcd_pcb_width/2 - i * lcd_hole_spacing_x/2, 6.5, 0])
                    cylinder(d=6.5, h=2, $fn=20);
            }
            for(i=[-1,1]) {
                translate([lcd_pcb_width/2 - i * lcd_hole_spacing_x/2, lcd_pcb_height -2.5, 0])
                    cylinder(d=3.5, h=2, $fn=20);
                translate([lcd_pcb_width/2 - i * lcd_hole_spacing_x/2, 6.5, 0])
                    cylinder(d=3.5, h=2, $fn=20);
            }
        }
    }
}
/* polygon([ [0,0], [35, 10], [0, height], [50, height], [50, 0]]); */


/* translate([width, 0, 13.5]) */ 
top_case();

