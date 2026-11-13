packing() {
    local VENDOR_BOOT_REPACK_SRC="$SCRIPTS_DIR/vendor_boot_repack.c"
    local VENDOR_BOOT_REPACK_BIN="$TMPDIR/vendor_boot_repack"

    if [ "$DO_ZIP" = "1" ] && [ -d "$AK3_DIR" ]; then
        echo -e "\n$(log_info "Building zip...")"

        log_info "Building vendor_boot v4 repacker..."
        clang --target=aarch64-linux-gnu -std=c11 -D_FILE_OFFSET_BITS=64 \
            -Os -static -s -o "$VENDOR_BOOT_REPACK_BIN" "$VENDOR_BOOT_REPACK_SRC" || exit 1

        cd "$AK3_DIR"
        rm -f vendor_boot.img dtb platform.dtb vendor_ramdisk_dlkm.lz4
        rm -rf vendor_modules
        cp -f "$TMPDIR/ramdisk_dlkm.lz4" vendor_ramdisk_dlkm.lz4
        cp -f "$OUT_DTBIMAGE" platform.dtb
        cp -f "$VENDOR_BOOT_REPACK_BIN" tools/vendor_boot_repack
        cp -f "$OUT_KERNEL" .
        zip -r9 -q "$ZIP_PATH" * -x .git .github README.md
        cd "$KDIR"
        echo -e "$(log_info "Done!") \n$(log_info "Output: $ZIP_PATH")\n"
        if [ "$AK3_TEST" != "1" ]; then
            rm -rf "$AK3_DIR"
        fi
    fi

    if [ "$DO_TAR" = "1" ]; then
        echo -e "\n$(log_info "Building TAR file...")"
        cd "$KDIR/kernel_build"
        rm -f "$TAR_PATH"
        lz4 -c -12 -B6 --content-size "$OUT_BOOTIMG" > boot.img.lz4 2>/dev/null
        lz4 -c -12 -B6 --content-size "$OUT_VENDORBOOTIMG" > vendor_boot.img.lz4 2>/dev/null
        if [ -f "$OUT_DTBOIMAGE" ]; then
            lz4 -c -12 -B6 --content-size "$OUT_DTBOIMAGE" > dtbo.img.lz4 2>/dev/null
            tar -cf "$TAR_PATH" boot.img.lz4 vendor_boot.img.lz4 dtbo.img.lz4
            rm -f boot.img.lz4 vendor_boot.img.lz4 dtbo.img.lz4
        else
            tar -cf "$TAR_PATH" boot.img.lz4 vendor_boot.img.lz4
            rm -f boot.img.lz4 vendor_boot.img.lz4
        fi
        cd "$KDIR"
        echo -e "$(log_info "Output: $TAR_PATH")"
    fi
}
