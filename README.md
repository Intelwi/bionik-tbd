# bionik-tbd

Projekt eksperymentalny/wewnętrzny. Korzystaj na własną odpowiedzialność.

## Konfiguracja systemu

### Arch Linux ARM: Raspberry Pi
[Instrukcja instalacji i wiki](https://archlinuxarm.org/platforms/armv6/raspberry-pi)

### Zainstalowane pakiety
```text
base-devel
fish
pacaur
vim
wiringpi
```

### Konfiguracja v4l2

Aby włączyć obsługę v4l2 należy utworzyć poniższe pliki konfiguracyjne. Dodatkowo, użytkownicy, który mają mieć prawo do korzystania z kamer (`/dev/videoX`) powinni być w grupie `video`.

###### /etc/modules-load.d/rpi-camera.conf
```text
bcm2835-v4l2
```

###### /etc/modprobe.d/rpi-camera.conf
```text
options bcm2835-v4l2 max_video_width=3240 max_video_height=2464
```

### Konfiguracja udev

Tworząc poniższy plik konfiguracyjny umożliwiamy użytkownikom z grupy `gpio` korzystać z GPIO.

###### /etc/udev/rules.d/raspberrypi.rules
```text
SUBSYSTEM=="bcm2835-gpiomem", GROUP="gpio", MODE="0660"

SUBSYSTEM=="gpio", GROUP="gpio", MODE="0660"
SUBSYSTEM=="gpio*", PROGRAM="/bin/sh -c '\
	chown -R root:gpio /sys/class/gpio && chmod -R 770 /sys/class/gpio;\
	chown -R root:gpio /sys/devices/virtual/gpio && chmod -R 770 /sys/devices/virtual/gpio;\
	chown -R root:gpio /sys$devpath && chmod -R 770 /sys$devpath\
'"
```

### Konfiguracja sieci

Tworzymy profil awaryjny. Jeśli nie uda się uzyskać adresu IP poprzez DHCP, adres jest ustawiany na `192.168.123.101`.

###### /etc/dhcpcd.conf
```text
# ...

# define static profile
profile static_eth0
static ip_address=192.168.123.101/24
static routers=192.168.123.100
static domain_name_servers=192.168.123.100

# fallback to static profile on eth0
interface eth0
fallback static_eth0
```

Zmieniamy zarządce sieci z `systemd-networkd` na `dhcpcd`.

```text
systemctl disable systemd-networkd.service
systemctl disable systemd-resolved.service
systemctl enable dhcpcd.service
```
