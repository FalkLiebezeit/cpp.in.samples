# mein_projekt.spec
# Dies ist eine einfache Spec-Datei für ein einfaches Testprojekt
Summary: Ein Testprojekt zum Packen einer eigenen RPM
Name: mein_projekt
Version: 0.1
Release: 1
Copyright: GPL
Group: misc/mein_projekt
Source: /usr/src/packages/SOURCES/mein_projekt/mein_projekt-0.1.tbz2
URL: none
Distribution: Debian Linux 11.0 (Bullseye)
Vendor: none
Packager: Rene Krooß <renekrooss@gmx.de>

%description
Bei diesem Paket handelt es sich um ein simples Beispiel,
um Ihnen das Erstellen eigener RPM-Pakete naeher zu erlaeutern.
%prep
%setup

%build
make

%install
cp "$RPM_BUILD_DIR"/mein_projekt-0.1/mein_projekt /usr/bin

%files
/usr/bin/mein_projekt
