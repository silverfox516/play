DESCRIPTION = "qt examples to study dbus"
SECTION = "applications"
LICENSE = "CLOSED"

DEPENDS += "qtbase"
RDEPENDS_${PN} += ""

SRC_URI = "git:///home/perso/igsong/myrepo/igsong-qt-example;branch=master"
SRCREV = "${AUTOREV}"

S = "${WORKDIR}/git"

inherit cmake cmake_qt5 pkgconfig

PACKAGE_ARCH = "${MACHINE_ARCH}"
EXTRA_OECMAKE = ""

RM_WORK_EXCLUDE += "${PN}"
