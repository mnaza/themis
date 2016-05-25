Summary: Data security library for network communication and data storage.
Name: themis-devel
Version: 0.9.3
Release: 1

Group: System Environment/Libraries
URL: http://cossacklabs.com/themis
Vendor: Cossack Labs Limited.
Packager: Andrey Mnatsakanov<andrey@cossacklabs.com>
License: Apache License, Version 2.0
Requires: openssl-devel

%description
Themis is a data security library, providing users with high-quality security
services for secure messaging of any kinds and flexible data storage. Themis
is aimed at modern developers, with high level OOP wrappers for Ruby, Python,
PHP, Java / Android and iOS / OSX. It is designed with ease of use in mind,
high security and cross-platform availability.

%prep

%build
make SECURE_COMPARATOR=enable

%install

%clean

%files
%defattr(-,root,root)
%attr(0755,root,root) %{_libdir}/libthemis.so

%changelog