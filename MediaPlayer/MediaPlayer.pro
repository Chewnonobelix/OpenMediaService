TEMPLATE = subdirs

SUBDIRS = \
    Application \
    Core \
    DesignLibrary \
    ExpressionLibrary \
    Plugins \
    UnitTest \
    UxComponent

Application.depends = Core
UnitTest.depends = Core Plugins
Core.depends = DesignLibrary ExpressionLibrary UxComponent
Plugins.depends = Core UxComponent
