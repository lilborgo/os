

u-boot:
	@bash scripts/u-boot.sh

mk-sd:
	@bash scripts/mk-sd.sh

clean:
	@yes | rm -f -r build/
	@mkdir build
