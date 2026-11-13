build_images() {
    local MONTH="$(date +%Y-%m)"

    echo -e "\n$(log_info "Building dtb image...")"
    python3 "$MKDTBOIMG" create "$OUT_DTBIMAGE" --custom0=0x00000000 --custom1=0xff000000 --version=0 --page_size=2048 "$IN_DTB" || exit 1

    local DTBO_FILES=("$OUTDIR/arch/arm64/boot/dts/samsung/$CODENAME/"*.dtbo)
    if [ -f "${DTBO_FILES[0]}" ]; then
        echo -e "$(log_info "Building dtbo image...")"
        local DTBO_ARGS=()
        local dtbo_file hw_min hw_max
        for dtbo_file in "${DTBO_FILES[@]}"; do
            hw_min=$(fdtget "$dtbo_file" / dtbo-hw_rev 2>/dev/null || echo "0")
            hw_max=$(fdtget "$dtbo_file" / dtbo-hw_rev_end 2>/dev/null || echo "$hw_min")
            DTBO_ARGS+=("$dtbo_file" "--custom0=$hw_min" "--custom1=$hw_max")
        done
        python3 "$MKDTBOIMG" create "$OUT_DTBOIMAGE" --page_size=2048 "${DTBO_ARGS[@]}" || exit 1
    fi

    "$MKBOOTIMG" --header_version 4 \
        --kernel "$OUT_KERNEL" \
        --output "$OUT_BOOTIMG" \
        --ramdisk "$PREBUILT_RAMDISK" \
        --os_version 15.0.0 \
        --os_patch_level "$MONTH" || exit 1
    echo -e "$(log_info "boot.img created!")"

    echo -e "\n$(log_info "Building vendor_boot image...")"
    cd "$DLKM_RAMDISK_DIR"
    find . | cpio --quiet -o -H newc -R root:root | lz4 -9cl > "../ramdisk_dlkm.lz4"

    clang -std=c11 -D_FILE_OFFSET_BITS=64 -Os \
        -o "$TMPDIR/vendor_boot_repack_host" \
        "$KDIR/kernel_build/scripts/vendor_boot_repack.c" || exit 1
    "$TMPDIR/vendor_boot_repack_host" "$PREBUILT_VENDOR_BOOT" \
        "$TMPDIR/ramdisk_dlkm.lz4" "$OUT_DTBIMAGE" \
        "$OUT_VENDORBOOTIMG" || exit 1

    cd "$KDIR"
    echo -e "$(log_info "Done!")"
}
