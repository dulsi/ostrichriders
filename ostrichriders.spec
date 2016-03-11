Summary: Knights flying on ostriches compete against other riders
Name: ostrichriders
Version: 0.6.3
Release: 1%{?dist}
License: GPLv3+
Url: http://www.identicalsoftware.com/ostrichriders
Group: Amusements/Games
Source: http://www.identicalsoftware.com/ostrichriders/%{name}-%{version}.tgz
BuildRequires: SFML-devel
BuildRequires: desktop-file-utils
BuildRequires: fontconfig-devel

%description
Enemy knights are invading the kingdom. As one of the elite ostrich riders,
it is your duty to defend the kingdom. With lance in hand you fly off.
Remember to stay above your opponent least you fall to his lance. Collect the
eggs least your opponent hatches stronger than before. Work togther with other
knights.

%prep
%setup -q

%build
make %{?_smp_mflags}

%install
make prefix=%{buildroot} install

%post
/bin/touch --no-create %{_datadir}/icons/hicolor &>/dev/null || :

%postun
if [ $1 -eq 0 ] ; then
    /bin/touch --no-create %{_datadir}/icons/hicolor &>/dev/null
    /usr/bin/gtk-update-icon-cache %{_datadir}/icons/hicolor &>/dev/null || :
fi

%posttrans
/usr/bin/gtk-update-icon-cache %{_datadir}/icons/hicolor &>/dev/null || :

%files
%doc README LICENCE
%{_bindir}/*
%{_datadir}/ostrichriders
%{_datadir}/icons/hicolor/*/apps/OstrichRiders.png
%{_datadir}/applications/ostrichriders.desktop
%{_datadir}/appdata/ostrichriders.appdata.xml

%changelog
* Thu Mar 10 2016 Dennis Payne <dulsi@identicalsoftware.com> - 0.6.3-1
- Moved install into the makefile.

* Thu Feb 11 2016 Dennis Payne <dulsi@identicalsoftware.com> - 0.6.2-1
- First ostrich riders spec file.
