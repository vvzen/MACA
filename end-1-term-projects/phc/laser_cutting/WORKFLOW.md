1. Make your model in Fusion360
2. Export to dxf (create a sketch for each face)
	
	2.1 Install Inkscape
	
	2.2 `sudo pip install lxml`
	
	2.3 ```python /Applications/Inkscape.app/Contents/Resources/share/inkscape/extensions/dxf_input.py --scale=25.4 your_file.dxf > your_file.svg```