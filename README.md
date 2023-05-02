# Tinywl versi lanjut

## Apa ini ?

### Tinywl dengan beberapa fitur tambahan. 

Fitur tambahan di antaranya :

- Fitur tap to click, untuk pengguna touchpad.
- Fungsi close / killclient lewat keybind.
- fungsi manipulasi jendela lewat keybind.
    - move ke kiri, kanan, atas, bawah dan tengah.
    - resize ke kiri, kanan, atas, bawah dan setengah tinggi dan lebar layar.
    - maximize jendela.
    - snap jendela ke pojok kiri, kanan, atas, bawah.
    - pseudo minimze.
- launcher (wofi).
- Protokol screencopy untuk mendukung screenshot.
- Protokol primary selection.
- Fitur warna background.
- Fungsi berpindah ke VT / virtual terminal.
- Zone eksklusif untuk menaruh bar.

Secara default shortcut yang tersedia :

- mod + enter : membuka terminal (foot).
- mod + p : membuka launcher (wofi).
- mod + h : maximize jendela arah vertikal ke sebelah kiri.
- mod + l : maximize jendela arah vertikal ke sebelah kanan.
- mod + shift + f : maximize jendela.
- mod + esc : keluar / quit kompositor.
- mod + q : menutup / close jendela.
- mod + j : mengirim jendela ke posisi paling bawah.
- mod + k : mengirim jendela ke posisi paling atas.
- mod + {left, right, up, down} : memindah / move jendela ke arah kiri, kanan, atas dan bawah.
- mod + shift + {l, h, k, j} : resize ukuran jendela ke arah kanan, kiri, atas, dan bawah.
- mod + shift + {r, e, t, w} : memindah jendela ke arah pojok kanan, kiri, atas, dan bawah.
- mod + Tab : cycle window.
- mod + {F1,F2,..F5} : berpindah ke virtual terminal 1 sampai 5.
- mod + z : toggle zona eksklusif.

## Cara *build*, *install* dan *run*.

Berikut adalah cara untuk *build*, menginstall dan *run* tinywl-next :

1. Sesuaikan pengaturan / konfigurasi di `config_tinywl.h` !
1. Sesuaikan keybind / shortcut di `tinywl.c` pada bagian fungsi `handle_keybinding` (opsional) ! 
1. *Build* dengan perintah `make` !
1. *Install* dengan perintah `make install` ! Tinywl-next akan terinstall di `$HOME/.local/bin/`.
1. Tinywl-next bisa langsung dijalankan dengan perintah `$HOME/.local/bin/tinywl`.

## Issue dan bug.

Ada beberapa issue dan bug yang kami temui di antaranya :

- Beberapa jendela tidak bisa di-resize dari pojok dan bagian atas, bawah, kanan, dan kiri (mpv dan imv).

    solusi : 

    - mpv : mendisable on-screen-controller dengan opsi `--no-osc`, bisa juga dengan menekan tombol delete.
    - imv : belum kami temukan.

- Bar / panel dan wallpaper setter tidak berjalan. Ini terjadi karena kami belum menerapkan layer shell protocol.

    solusi :

    - Untuk bar / panel, bisa menggunakan lxqt-panel dan ditaruh di pojok kiri (snap ke kiri / Alt + e).
    - Untuk wallpaper masih dalam pengembangan.
