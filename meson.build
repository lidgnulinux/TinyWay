project(
	'tinywl',
	'c',
	version: '0.1',
	license: 'MIT',
	meson_version: '>=0.59.0',
	default_options: [
		'c_std=c11',
		'warning_level=2',
		'werror=true',
	],
)

add_project_arguments(
  [
    '-DWLR_USE_UNSTABLE',
    '-Wundef',
    '-Wno-unused-parameter',
    '-Wno-error=uninitialized',
  ],
  language: 'c',
)

wl_protocol_dir = dependency('wayland-protocols', version: '>=1.42').get_variable('pkgdatadir')
protocols_being_used = [
  [wl_protocol_dir, 'stable/xdg-shell/xdg-shell.xml'],
]

headers_for_protocols_being_used = []
foreach protocol : protocols_being_used
  xml = join_paths(protocol)
  headers_for_protocols_being_used += generator(
    find_program('wayland-scanner'),
    output: '@BASENAME@-protocol.h',
    arguments: ['server-header', '@INPUT@', '@OUTPUT@'],
  ).process(xml)
endforeach

executable(
  meson.project_name(),
  'tinywl.c',
  dependencies: [
    dependency('wlroots-0.19', version: '>= 0.19', fallback: ['wlroots', 'wlroots']),
    dependency('wayland-server'),
    dependency('xkbcommon'),
    dependency('libinput'),
    declare_dependency(
      sources: headers_for_protocols_being_used,
    ),
  ],
  install: true,
)
