Name:           harbour-mumble
Version:        1.3.0
Release:        1
License:        BSD
BuildRoot:      %{_tmppath}/%{name}-%{version}-build
Group:          Applications/Multimedia
Summary:        A voice chat application similar to TeamSpeak
BuildRequires:  protobuf-devel libpng-devel openssl-devel libsndfile-devel boost-devel pulseaudio-devel
Requires: libsndfile
Source:	https://github.com/mumble-voip/mumble/releases/download/%{version}/mumble-%{version}.tar.gz

%description
Mumble is an open source, low-latency, high quality voice chat software primarily intended for use while gaming.

%prep
%setup

%build
qmake main.pro \
    CONFIG+="bundled-opus bundled-celt bundled-speex no-g15 no-xevie no-speechd no-server no-overlay no-plugins no-embed-qt-translations no-update no-bonjour no-alsa no-oss no-x11 packaged" \
    DEFINES+="PLUGIN_PATH=/usr/share/harbour-mumble/lib" \
    LIBS+="-lpng16 -lfreetype -lfontconfig" \
    QMAKE_RPATHDIR+="/usr/share/harbour-mumble/lib"
	
make release

%install
install -m 755 -d %{buildroot}/usr/share/harbour-mumble/lib
install -m 755 -D ./mumble %{buildroot}/usr/bin/harbour-mumble

install -m755 -D ./libcelt* %{buildroot}/usr/share/harbour-mumble/lib/
install -m755 -D ./libopus* %{buildroot}/usr/share/harbour-mumble/lib/
ln -s ./libopus.so.0.0.0 %{buildroot}/usr/share/harbour-mumble/lib/libopus.so.0

install -m644 -D %{_sourcedir}/../scripts/mumble.desktop %{buildroot}/usr/share/applications/harbour-mumble.desktop
#install -m755 -d %{buildroot}/usr/share/man/man1
#install -m644 -D %{_sourcedir}/../man/mum* %{buildroot}/usr/share/man/man1/
install -m644 -D %{_sourcedir}/../icons/172x172/harbour-mumble.png %{buildroot}/usr/share/icons/hicolor/172x172/apps/harbour-mumble.png
install -m644 -D %{_sourcedir}/../icons/86x86/harbour-mumble.png %{buildroot}/usr/share/icons/hicolor/86x86/apps/harbour-mumble.png

#install -m644 -D %{_sourcedir}/../scrips/harbour-mumble.conf %{buildroot}/etc/pulse/xpolicy.conf.d/

desktop-file-install --delete-original       \
  --dir %{buildroot}%{_datadir}/applications             \
   %{buildroot}%{_datadir}/applications/*.desktop
  
%files
%defattr(-,root,root)
%{_bindir}/harbour-mumble
/usr/share/harbour-mumble/lib/*
#%{_mandir}/man1/mum*
%{_datadir}/applications/harbour-mumble.desktop
/usr/share/icons/hicolor/*/apps/harbour-mumble.png
#/etc/pulse/xpolicy.conf.d/*

%changelog
