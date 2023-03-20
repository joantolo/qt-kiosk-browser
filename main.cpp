/*
 * Copyright (c) 2023 Joan Torres  <joan.torres@suse.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <QApplication>
#include <QScreen>
#include <QWebEngineSettings>
#include <QWebEngineView>

QUrl commandLineUrlArgument()
{
    const QStringList args = QCoreApplication::arguments();
    for (const QString &arg : args.mid(1)) {
        if (!arg.startsWith(QLatin1Char('-')))
            return QUrl::fromUserInput(arg);
    }

    qWarning() << "Didn't receive a valid url as an argument.";
    return QUrl();
}

void setSettings(QWebEngineView &view)
{
    QWebEngineSettings *settings = view.settings();
    settings->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);

    view.setWindowFlag(Qt::WindowType::FramelessWindowHint, true);
}

int main(int argc, char *argv[])
{
    setenv("QTWEBENGINE_DISABLE_SANDBOX", "1", true); // Needed to run as root

    QApplication app(argc, argv);
    QWebEngineView view;

    setSettings(view);
    view.setUrl(commandLineUrlArgument());
    view.resize(app.screens().first()->availableSize());
    view.showFullScreen();

    return app.exec();
}
