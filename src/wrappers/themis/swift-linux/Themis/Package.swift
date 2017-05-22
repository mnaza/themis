import PackageDescription

let package = Package(
    name: "Themis",
    dependencies: [
        .Package(url: "https://github.com/mnaza/themis/src/wrappers/themis/swift-linux/CThemis", majorVersion: 1)
    ]
)
