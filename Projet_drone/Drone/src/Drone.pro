#-------------------------------------------------
#
# Project created by QtCreator 2023-01-16T14:55:56
#
#-------------------------------------------------

TARGET = DRONE
TEMPLATE = app

QT += core gui printsupport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
# greaterThan(QT_MAJOR_VERSION, 4): QT += multimedia

# --- Gestion src/ build/ bin/ ---
BASE_DIR	= ".."
BUILD_DIR	= "$${BASE_DIR}/build"
BIN_DIR		= "$${BASE_DIR}/bin"
CODE_DIR	= "$${BASE_DIR}/src/app"
COTS_DIR	= "$${BASE_DIR}/src/cots"
DLL_DIR         = "$${BASE_DIR}/src/dll"
SCRIPTS_DIR	= "$${BASE_DIR}/src/scripts"
RESOURCES_DIR   = "$${BASE_DIR}/src/app/resources"

# Fichiers temporaires dans le répertoire build/
RCC_DIR		= "$${BUILD_DIR}"
UI_DIR		= "$${BUILD_DIR}"
MOC_DIR		= "$${BUILD_DIR}"
OBJECTS_DIR	= "$${BUILD_DIR}"
PRECOMPILED_DIR = "$$OBJECTS_DIR"

CONFIG += debug_and_release
CONFIG(debug, debug|release) {
        DESTDIR = "$$BIN_DIR/debug"
        # On ne copie pas les dll en debug
        # (on n'utilisera que les versions release pour les versions finales)
} else:CONFIG(release, debug|release) {
        DESTDIR = "$$BIN_DIR/release"

        # Copie des dll utiles dans le répertoire release
        win32 {
            # La commande "copy" de Windows n'accepte pas les chemins d'accès avec des slash, on les remplace donc par des backslash
            DESTDIR_WIN = $${DESTDIR}
            DESTDIR_WIN ~= s,/,\\,g
            SCRIPTS_DIR_WIN	= $${SCRIPTS_DIR}
            SCRIPTS_DIR_WIN ~= s,/,\\,g
            RESOURCES_DIR_WIN   = $${RESOURCES_DIR}
            RESOURCES_DIR_WIN   ~= s,/,\\,g
            COTS_DIR_WIN = $${COTS_DIR}
            COTS_DIR_WIN ~= s,/,\\,g
            DLL_DIR_WIN = $${DLL_DIR}
            DLL_DIR_WIN ~= s,/,\\,g

            postbuild.target          = postbuild
            postbuild.depends        += FORCE
            greaterThan(QT_MAJOR_VERSION, 4) {
                # Qt5
                # windeployqt récupère automatiquement toutes les dll requises
                QMAKE_POST_LINK = windeployqt.exe "$$DESTDIR_WIN"
                QMAKE_POST_LINK += & CMD /c "$$SCRIPTS_DIR_WIN\\copy_dll.bat"
                #postbuild.commands       = "$$SCRIPTS_DIR_WIN\\copy_dll.bat"
            } else {
                # Qt4
                # Commande de copie des 4 dll requises
                postbuild.commands   =   copy "$$QMAKE_LIBDIR_QT\\QtGui4.dll" "$$DESTDIR_WIN"
                postbuild.commands  += & copy "$$QMAKE_LIBDIR_QT\\QtCore4.dll" "$$DESTDIR_WIN"
                postbuild.commands  += & copy "$$QMAKE_LIBDIR_QT\\..\\..\\..\\..\\..\\mingw\\bin\\mingwm10.dll" "$$DESTDIR_WIN"
                postbuild.commands  += & copy "$$QMAKE_LIBDIR_QT\\..\\..\\..\\..\\..\\mingw\\bin\\libgcc_s_dw2-1.dll" "$$DESTDIR_WIN"

                # postbuild.commands  += & xcopy /S /I /Y /C "$$RESOURCES_DIR_WIN\\sounds" "$$DESTDIR_WIN\\sounds"
                # postbuild.commands  += & xcopy /S /I /Y /C "$$RESOURCES_DIR_WIN\\ini" "$$DESTDIR_WIN\\ini"
                # postbuild.commands  += & xcopy /E /I /Y /C "$$DLL_DIR_WIN\\serial_reprog_widget\\resources" "$$DESTDIR_WIN\\resources"
                # postbuild.commands  += & "$$SCRIPTS_DIR_WIN\\copy_dll.bat 2>&1"
                postbuild.commands       += & "$$SCRIPTS_DIR_WIN\\copy_dll.bat"
            }
            PRE_TARGETDEPS            = postbuild
            QMAKE_EXTRA_TARGETS      += postbuild
        }
} else {
    error(Unknown set of dependencies.)
}

include($${CODE_DIR}/app.pri)
