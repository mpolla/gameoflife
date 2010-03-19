# This file is part of gameoflife.

# Volume Unit is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 2 of the License, or (at your
# option) any later version.

# Volume Unit is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with Volume Unit; if not, write to the Free Software Foundation,
# Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

AM_CFLAGS = -Wall -O2 -DPKG_DATA_DIR=\"$(pkgdatadir)\"

bin_PROGRAMS = gameoflife

EXTRA_DIST = *.h

gameoflife_SOURCES = gameoflife.c
gameoflife_LDFLAGS = -lncurses
