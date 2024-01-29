

u-boot:
	@bash scripts/u-boot.sh

img:
	@bash scripts/img.sh

clean:
	@yes | rm -f -r build/
	@mkdir build
