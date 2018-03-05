for f in *.dxf
do 
filename="${f%.*}"
echo "converting $filename"
python /Applications/Inkscape.app/Contents/Resources/share/inkscape/extensions/dxf_input.py --scale=25.4 "$f" > "$filename.svg"
done
