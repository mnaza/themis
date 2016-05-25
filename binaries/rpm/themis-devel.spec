Summary: Data security library for network communication and data storage.
Name: themis
Version: 0.9.3
Release: 1
Group: System Environment/Libraries
URL: http://cossacklabs.com/themis
Vendor: Cossack Labs Limited.
Packager: Andrey Mnatsakanov<andrey@cossacklabs.com>
License: Apache License, Version 2.0
Requires: openssl-devel
Source: https://github.com/cossacklabs/themis/archive/0.9.3.tar.gz

%description
Themis is a data security library, providing users with high-quality security
services for secure messaging of any kinds and flexible data storage. Themis
is aimed at modern developers, with high level OOP wrappers for Ruby, Python,
PHP, Java / Android and iOS / OSX. It is designed with ease of use in mind,
high security and cross-platform availability.

%prep
%setup -q

%build
make SECURE_COMPARATOR=enable

%install
make SECURE_COMPARATOR=enable PREFIX=%{buildroot}/usr install
mkdir -p %{buildroot}/usr/include/soter/openssl
mkdir -p %{buildroot}/usr/include/soter/ed25519
cp src/soter/openssl/*.h %{buildroot}/usr/include/soter/openssl
cp src/soter/ed25519/*.h %{buildroot}/usr/include/soter/ed25519


%clean
rm -rf $RPM_BUILD_ROOT
%post
ldconfig
echo " "
echo "Installation of Themis Complete!"

%files
/usr/lib/libthemis.so
/usr/lib/libsoter.so
/usr/lib/libthemis.a
/usr/lib/libsoter.a
/usr/include/soter/*.h
/usr/include/soter/**/*.h
/usr/include/themis/*.h
