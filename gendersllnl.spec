Name: 
Version:
Release:
Summary: LLNL site specific genders library
Copyright: none
Group: System Environment/Base
Source0:
Requires: genders >= 1.1
BuildRoot: %{_tmppath}/%{name}-%{version}

%description
A LLNL genders site specific library 

%package dist
Summary: gendersllnl dist 
Group: System Environment/Base
%description dist
file distribution tool

%prep
%setup  -q -n %{name}-%{version}

%build
./configure --prefix=/usr --with-xs-prefix="$RPM_BUILD_ROOT/usr" --with-gendersllnl-pm-prefix="$RPM_BUILD_ROOT/usr" --with-compat-prefix="$RPM_BUILD_ROOT/usr"
make 

%install
rm -rf $RPM_BUILD_ROOT
DESTDIR="$RPM_BUILD_ROOT" make install 

%files
%defattr(-,root,root)
%doc README ChangeLog COPYING
/usr/man/man3/
/usr/share/man/man3/
/usr/include/gendersllnl.h
/usr/lib/

%files dist
%defattr(-,root,root)
%doc dist/TUTORIAL dist/Distfile.sample
/usr/man/man1/*
/usr/bin/
