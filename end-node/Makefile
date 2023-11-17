# name of your application
APPLICATION = end-node

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= ../RIOT

USEMODULE += netdev_default
USEMODULE += auto_init_gnrc_netif
USEMODULE += gnrc_ipv6_default

USEMODULE += gcoap

USEMODULE += od
USEMODULE += fmt
USEMODULE += netutils
USEMODULE += random

GCOAP_ENABLE_DTLS ?= 1

# Required by DTLS.
USEPKG += tinydtls
USEMODULE += sock_dtls
USEMODULE += tinydtls_sock_dtls
USEMODULE += gcoap_dtls
# tinydtls needs crypto secure PRNG
USEMODULE += prng_sha1prng

USEMODULE += ztimer
USEMODULE += ztimer_msec

# temperture sensor
USEMODULE += lps331ap

# ambient light sensor
USEMODULE += isl29020

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Uncomment this to join RPL DODAGs even if DIOs do not contain
# DODAG Configuration Options (see the doc for more info)
# CFLAGS += -DCONFIG_GNRC_RPL_DODAG_CONF_OPTIONAL_ON_JOIN

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

EXTERNAL_BOARD_DIRS += $(RIOTBASE)/tests/build_system/external_board_dirs/esp-ci-boards

include $(RIOTBASE)/Makefile.include

# Set a custom channel if needed
include $(RIOTMAKE)/default-radio-settings.inc.mk

#enable debug prints
CFLAGS += -DUSE_DPRINT=y
CFLAGS += -DCONFIG_DTLS_PSK
