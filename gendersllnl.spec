Name: 
Version:
Release:
Summary: LLNL site specific genders library
Copyright: none
Group: System Environment/Base
Source0:
Prereq: genders
BuildRoot: %{_tmppath}/%{name}-%{version}

%description
A LLNL genders site specific library 

%prep
%setup  -q -n %{name}-%{version}

%build
./configure --prefix=/usr
make 

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/usr/man/man3
mkdir -p $RPM_BUILD_ROOT/usr/share/man/man3
cd man/; gzip *.3; cd ..
install man/libgendersllnl.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/gendersllnl.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_getaltnodes.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_isaltnode.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_altnodelist.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_altnodelist_create.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_get_cluster.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_getaltnodes_preserve.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_isnode_or_altnode.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_altnodelist_clear.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_altnodelist_destroy.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_to_gendname.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_to_altname.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_to_gendname_preserve.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_to_altname_preserve.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_to.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_string_to_gendnames.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_string_to_altnames.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_string_to_gendnames_preserve.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_string_to_altnames_preserve.3.gz $RPM_BUILD_ROOT/usr/man/man3
install man/genders_string.3.gz $RPM_BUILD_ROOT/usr/man/man3
cp src/libgendersllnl/gendersllnl.h src/Libgendersllnl	
cp src/libgendersllnl/gendersllnl.c src/Libgendersllnl	
cp src/libgendersllnl/hostlist.h src/Libgendersllnl	
cp src/libgendersllnl/hostlist.c src/Libgendersllnl	
cd src/Libgendersllnl; perl Makefile.PL prefix="$RPM_BUILD_ROOT/usr"; make; make pure_install; cd ../..
DESTDIR="$RPM_BUILD_ROOT" make install 

%files
%defattr(-,root,root)
%doc README ChangeLog DISCLAIMER COPYING
/usr/man/man3/libgendersllnl.3.gz 
/usr/man/man3/gendersllnl.3.gz 
/usr/man/man3/genders_getaltnodes.3.gz 
/usr/man/man3/genders_isaltnode.3.gz 
/usr/man/man3/genders_altnodelist.3.gz 
/usr/man/man3/genders_altnodelist_create.3.gz 
/usr/man/man3/genders_get_cluster.3.gz 
/usr/man/man3/genders_getaltnodes_preserve.3.gz 
/usr/man/man3/genders_isnode_or_altnode.3.gz 
/usr/man/man3/genders_altnodelist_clear.3.gz 
/usr/man/man3/genders_altnodelist_destroy.3.gz 
/usr/man/man3/genders_to_gendname.3.gz 
/usr/man/man3/genders_to_altname.3.gz 
/usr/man/man3/genders_to_gendname_preserve.3.gz 
/usr/man/man3/genders_to_altname_preserve.3.gz 
/usr/man/man3/genders_to.3.gz 
/usr/man/man3/genders_string_to_gendnames.3.gz 
/usr/man/man3/genders_string_to_altnames.3.gz 
/usr/man/man3/genders_string_to_gendnames_preserve.3.gz 
/usr/man/man3/genders_string_to_altnames_preserve.3.gz 
/usr/man/man3/genders_string.3.gz 
/usr/include/gendersllnl.h
/usr/lib/libgendersllnl.*
/usr/lib/perl5/
