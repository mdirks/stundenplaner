/***************************************************************************
 *   Copyright (C) 2009, 2011, 2012 by Glad Deschrijver                    *
 *     <glad.deschrijver@gmail.com>                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.  *
 ***************************************************************************/

#include "zoomaction.h"

#include <QtGui/QIcon>
#include "globallocale.h"

ZoomAction::ZoomAction(QObject *parent, const QString &name)
	: SelectAction(parent, name)
{
	init();
}

ZoomAction::ZoomAction(const QString &text, QObject *parent, const QString &name)
	: SelectAction(text, parent, name)
{
	init();
}

ZoomAction::ZoomAction(const QIcon &icon, const QString &text, QObject *parent, const QString &name)
	: SelectAction(icon, text, parent, name)
{
	init();
}

void ZoomAction::init()
{
	setEditable(true);
#ifndef QT_NO_TOOLTIP
	setToolTip(tr("Select or insert zoom factor here"));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
	setWhatsThis(tr("<p>Select the zoom factor here.  "
	                "Alternatively, you can also introduce a zoom factor and "
	                "press Enter.</p>"));
#endif // QT_NO_WHATSTHIS
	setCurrentZoomFactor();
	connect(this, SIGNAL(triggered(QString)), this, SLOT(setZoomFactor(QString)));
}

ZoomAction::~ZoomAction()
{
}

void ZoomAction::setMinZoomFactor(qreal zoomFactor)
{
	m_minZoomFactor = zoomFactor;
}

void ZoomAction::setMaxZoomFactor(qreal zoomFactor)
{
	m_maxZoomFactor = zoomFactor;
}

qreal ZoomAction::minZoomFactor() const
{
	return m_minZoomFactor;
}

qreal ZoomAction::maxZoomFactor() const
{
	return m_maxZoomFactor;
}

static QString formatZoomFactor(qreal zoomFactor)
{
	QString zoomFactorText = GlobalLocale::formatNumber(zoomFactor, 2);
	const QString decimalSymbol = GlobalLocale::decimalSymbol();

	zoomFactorText.remove(decimalSymbol + QLatin1String("00"));
	// remove trailing zero in numbers like 12.30
	if (zoomFactorText.endsWith(QLatin1Char('0'))
	        && zoomFactorText.indexOf(decimalSymbol) >= 0)
		zoomFactorText.chop(1);

	zoomFactorText += QLatin1Char('%');
	return zoomFactorText;
}

void ZoomAction::setCurrentZoomFactor(qreal newZoomFactor)
{
	const qreal zoomFactorArray[] = {12.50, 25, 50, 75, 100, 125, 150, 200, 250, 300};
	const int zoomFactorNumber = 10;
    QStringList zoomFactorList;
	int newZoomFactorPosition = -1;
	bool addNewZoomFactor = true;

    zoomFactorList << "fit"; //MD

	if (newZoomFactor < m_minZoomFactor || newZoomFactor > m_maxZoomFactor)
		addNewZoomFactor = false;

	newZoomFactor *= 100;
	for (int i = 0; i < zoomFactorNumber; ++i)
	{
		if (addNewZoomFactor && newZoomFactor < zoomFactorArray[i])
		{
			zoomFactorList << formatZoomFactor(newZoomFactor);
			newZoomFactorPosition = i;
			addNewZoomFactor = false;
		}
		else if (newZoomFactor == zoomFactorArray[i])
		{
			newZoomFactorPosition = i;
			addNewZoomFactor = false;
		}
		zoomFactorList << formatZoomFactor(zoomFactorArray[i]);
	}
	if (addNewZoomFactor)
	{
		zoomFactorList << formatZoomFactor(newZoomFactor);
		newZoomFactorPosition = zoomFactorNumber;
	}

	disconnect(this, SIGNAL(triggered(QString)), this, SLOT(setZoomFactor(QString)));
	clear();
	setItems(zoomFactorList);
	if (newZoomFactorPosition >= 0)
		setCurrentIndex(newZoomFactorPosition);
	connect(this, SIGNAL(triggered(QString)), this, SLOT(setZoomFactor(QString)));
}

void ZoomAction::setZoomFactor(qreal zoomFactor)
{
	// adjust zoom factor
	zoomFactor = qBound(m_minZoomFactor, zoomFactor, m_maxZoomFactor);

	// add current zoom factor to the list of zoom factors
	const QString zoomFactorString = formatZoomFactor(zoomFactor * 100);
	const int zoomFactorIndex = items().indexOf(zoomFactorString);
	if (zoomFactorIndex >= 0)
		setCurrentIndex(zoomFactorIndex);
	else
		setCurrentZoomFactor(zoomFactor);

	Q_EMIT zoomFactorAdded(zoomFactor);
}

void ZoomAction::setZoomFactor(const QString &zoomFactorText)
{
    if(zoomFactorText == "fit"){
        m_fit=true;
        //QSize s=m_view->size();
        //m_view->resize(s);

        //m_view->setZoomFactor(.74*widht/pwidht);
    } else {
        m_fit=false;
        setZoomFactor(GlobalLocale::readNumber(QString(zoomFactorText).remove(QRegExp(QString(QLatin1String("[^\\d\\%1]*")).arg(GlobalLocale::decimalSymbol())))) / 100.0);
    }
}

void ZoomAction::setView(PdfView *v)
{
    m_view=v;
}

PdfView* ZoomAction::getView()
{
    return m_view;
}
