oscad = /Applications/OpenSCAD.app/Contents/MacOS/OpenSCAD
main = scad/enclosure.scad
configuration_file = scad/configuration.scad
output_dir = stl/

all:$(output_dir)front.stl $(output_dir)top.stl $(output_dir)spacers.stl

$(output_dir)front.stl: $(main) $(configuration_file)
	$(oscad) -o $@ -D draw_complete=0 -D draw_front=1 $(main)

$(output_dir)top.stl: $(main) $(configuration_file)
	$(oscad) -o $@ -D draw_complete=0 -D draw_top=1 $(main)

$(output_dir)spacers.stl: $(main) $(configuration_file)
	$(oscad) -o $@ -D draw_complete=0 -D draw_spacers=1 $(main)

clean:
	rm $(output_dir)*.stl
