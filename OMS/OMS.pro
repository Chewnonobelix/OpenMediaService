TEMPLATE = subdirs

CONFIG = ordered

SUBDIRS = \
    DesignLibrary \
    ExpressionLibrary \
    UxComponent \
    Core \
    Application \
    Plugins \
#    UnitTest \
#    ManulTest \

TRANSLATIONS += Tr\Francais.ts \
                Tr\English.ts

Application.depends = Core
#UnitTest.depends = Core Plugins
Core.depends = DesignLibrary ExpressionLibrary UxComponent
Plugins.depends = Core UxComponent
