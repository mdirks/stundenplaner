//
// C++ Implementation: latexoutput
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "latexoutput.h"

#include <KRun>
#include <list>
#include <map>
#include <string>
#include <QDebug>
#include <QProcess>

#include "datamodel/krusbucheintrag.h"
#include "datamodel/schueler.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryentry.h"
#include "orm/repository/repositoryproperty.h"
#include "utils/datecompare.h"

LatexOutput::LatexOutput(QString t, QString& filename)
	: QFile(filename), title(t)
{   
    if ( this->open(QIODevice::WriteOnly) ) {
        this-> stream = new QTextStream( this );
    //stream->setEncoding(QTextStream::Latin1);
	writeHeader();
    } else {
	stream = 0;
    }



}


LatexOutput::~LatexOutput()
{
        //close();

}

void LatexOutput::close()
{
	writeFooter();
	QFile::close();
}

void LatexOutput::edit()
{
    qDebug() << QString("Editing %1").arg(this->fileName());

    //KRun::runCommand(QString("texmaker %1").arg(this->fileName()),0);

    QString prog=QString("texmaker");
    QStringList args;
    args << QString(this->fileName());

    QProcess *p  = new QProcess(this);
    /*p->setStandardErrorFile(QString("/home/mopp/err%2.txt").arg(parent->getID()),
                            QIODevice::Append);
    p->setStandardOutputFile(QString("/home/mopp/out%2.txt").arg(parent->getID()),
                            QIODevice::Append);
    */

    qDebug() << prog << args;

    p->start(prog,args);
    if(!p->waitForStarted()){
        qDebug() << "Process could not be started";
    }

}



void LatexOutput::writeHeader()
{
	if(stream){
		*stream << "\\documentclass[a4paper,10pt]{article} \n\
\\usepackage{mdstd} \n\
\n\
\\begin{document} \n\n";
	}
}

void LatexOutput::writeFooter()
{
	if(stream)
	{
		*stream << "\\end{document} \n";
	}
}

void LatexOutput::write( stunde *st)
{
	if(stream){
        *stream << "\\stunden{" << st->getTitle().c_str() << "}{\n" << st->getVerlauf().c_str() << "\n}\n\n";
	}
}

void LatexOutput::write( stundenplaneintrag *se)
{
	if(stream){
        *stream << "\\stunden{" << se->getName().c_str() << "}{\n" << se->getVerlauf().c_str() << "\n}\n\n";
	}
}

void LatexOutput::write( notiz *n)
{
	if(stream){
        *stream << "\\notizn{" << n->getName().c_str() << "}{\n" << n->getBody().c_str() << "\n}\n\n";
	}
}

void LatexOutput::write(schultag *scht)
{
	*stream << "\\titlebox{ " << scht->getDatum().date().toString("dddd dd MM") << "} \n\
\\mainframe{ \n";

	list<stundenplaneintrag*> *list_eintr=scht->getEintraege();
	list_eintr->sort();
	for(list<stundenplaneintrag*>::iterator it=list_eintr->begin(); it != list_eintr->end(); it++){
		write(*it);
	}

	*stream << "} % end mainframe \n\n";
}



void LatexOutput::write( WeekMap *wm )
{
    qDebug() << "WARNING: NOT IMPLEMENTED  LatexOutput::write( WeekMap *wm )";
    /*
    *stream << "\\titlebox{ " << wm->getName().c_str() << "} \n\
\\mainframe{ \n";


	list<PObjectCanvasItem*> *items = wm->getCanvasItems();
	 for(list<PObjectCanvasItem*>::iterator it=items->begin(); it != items->end(); it++)
	{
		PObjectCanvasItem *item = (*it);
		PObject *o = item->getObject();
		write (o);
	} 

	*stream << "} % end mainframe \n\n";
    */
}

void LatexOutput::write( PObject *o)
{
	if(stunde *st = dynamic_cast<stunde*>(o)){
		write(st);
	}  else if(stundenplaneintrag *se = dynamic_cast<stundenplaneintrag*>(o)){
		write(se);
	}  else if (notiz *n = dynamic_cast<notiz*>(o)){
		write(n);
	} else if( WeekMap *wm = dynamic_cast<WeekMap*>(o)){
		write(wm);
	} else if( schultag *scht = dynamic_cast<schultag*>(o)){
		write(scht);
	} else if( kursbuch *kb = dynamic_cast<kursbuch*>(o)){
		write(kb);
	} else if( teilleistung *tl = dynamic_cast<teilleistung*>(o)){
		write(tl);
	} else {
        qDebug() << QString("LatexOutput::write : Warning : write not implemented for %1").arg(o->getPersistenceObject()->getClassName().c_str());
	}

}

void LatexOutput::write( kursbuch *kb)
{
	if(stream){
		*stream << "\\renewcommand{\\arraystretch}{3.2} \n";
	
		*stream << "\n\n \\vspace*{2cm} \n\n";

		*stream << "\n {\\bf Leistungskurs} \\\\[.5cm] \\begin{tabular}{|p{10cm}|p{7cm}|} \n";
		*stream << "\\hline \n";
		*stream << "\\multicolumn{2}{|p{17cm}|}{\\small Kurs-Nr.} \\\\ \\hline \n";
		*stream << "Kurs-Leiter & Fach \\\\ \\hline";
		*stream << "\\multicolumn{2}{|p{17cm}|}{\\small Thema} \\\\  \\hline \n";
		*stream << " 1.Halbjahr \\hspace*{2cm} 2. Halbjahr & Jahr \\\\ \\hline \n";
		*stream << "\\hline";
		*stream << "\\end{tabular}\n \\newpage \n\n";

		

		list<krusbucheintrag*> *list_kbe = kb->getEintraege();
		RepositoryEntry *re = Repository::getInstance()->getRepositoryEntry("krusbucheintrag");
		RepositoryProperty *r= re->getProperty("Datum");
		list_kbe->sort(DateCompare<PObject>(r));

		
		list<teilleistung*> *list_tl = new list<teilleistung*>();
		list_tl->push_back( kb->getKlausur1a() );
		list_tl->push_back( kb->getKlausur1b());
		list_tl->push_back( kb->getAt1() );
		list_tl->push_back( kb->getG1() );
		list_tl->push_back( kb->getKlausur2a() );
		list_tl->push_back( kb->getKlausur2b());
		list_tl->push_back( kb->getAt2() );
		list_tl->push_back( kb->getG2() );
				
				

		/* 
			Tabelle Namen
		*/
		list<schueler*> *list_sch = kb->getKlasse()->getSchueler();
		int n_schueler = list_sch->size();
		if(n_schueler < 27){
			*stream << "\\renewcommand{\\arraystretch}{2.3} \n";
		} else {
			*stream << "\\renewcommand{\\arraystretch}{1.9} \n";
		}
		*stream << "\\begin{tabular}{|p{4cm}|c}\n \\hline\n";
		*stream << "{\\bf Nachname,  Vorname} & \\hspace*{13.5cm} \\\\ \n & \\\\ \\hline \n";
		
		for(list<schueler*>::iterator it=list_sch->begin(); it != list_sch->end(); it++){
			schueler *s = *it;
            *stream << s->getNachname().c_str() << ", " << s->getVorname().c_str();
			*stream << " & \\\\ \\hline \n";
		}
		for(int i=26-n_schueler; i>0; i--){
			*stream << " & \\\\ \\hline \n";
		}
		*stream << " \\end{tabular} \n \\newpage \n\n";
		
		/*
			Tabelle Noten
		*/
		*stream << "\\begin{tabular}{";
		for(int i=0; i<10; i++){
			*stream << "p{1.0cm}|";
		} 
		*stream << "}\n \\hline  \n";
		*stream << "\\multicolumn{5}{c|}{1. Halbjahr} & \\multicolumn{5}{c|}{2. Halbjahr} \\\\ \n";
		*stream << " Kl 1 & Kl 2 & AT & Punkte & Note & Kl 1 & Kl 2 & AT & Punkte & Note \\\\ \n \\hline \n";
		//list<schueler*> *list_sch = kb->getKlasse()->getSchueler();
		for(list<schueler*>::iterator it=list_sch->begin(); it != list_sch->end(); it++){
			schueler *s = *it;
			int i=0;
			for(list<teilleistung*>::iterator itt=list_tl->begin(); itt != list_tl->end(); itt++){
				teilleistung *tl = *itt;
				if(tl){
					note *n = tl->getNote(s);
					if(n){
						*stream  << n->getPunkte() << " & "; 
					} else {
						*stream << " & ";
					}
					if(i==3){
						if(n) *stream << punkteToNote(n->getPunkte()); 
						*stream << " &";
					} else if(i==7){
						if(n) *stream << punkteToNote(n->getPunkte()); 
					}
				} else {
					*stream << " &";
				}
				i++;
			}
			*stream << "\\\\ \n \\hline \n";
		}
		for(int i=26-n_schueler; i>0; i--){
			*stream << "  & & & & & & & & &  \\\\ \\hline \n";
		}
		*stream << "\\end{tabular} \n \\newpage \n\n";
		

		/*
			Tabelle Fehlzeiten
		*/
		int size = list_kbe->size();

		int n_page = 0;
		int n_size = size;
		int p_size = 15;
		while(n_size > 0){
			n_page++;
			n_size=n_size-p_size;
		}
        qDebug() << QString("Calculated number of pages %1").arg(n_page);

		for(int i=0; i<n_page; i++){
			*stream << "\\vspace*{-.2cm} \n";
			*stream << "\\begin{tabular}{";
            qDebug() << QString("Writing page %1, size is %2").arg(i).arg(p_size);
			

			int offset=i*p_size;
			
			for(int j=0; j<p_size;j++){
				*stream << "p{.5cm}|";
			} 
			*stream << "}\n \\hline  \n";
			list<krusbucheintrag*>::iterator itt = list_kbe->begin();
			for(int j=0; j<offset; j++) itt++;
			for(int j=0; j<p_size; j++){
					if(itt != list_kbe->end()){
						krusbucheintrag *ke = (*itt);
						*stream << " {\\bf " << ke->getDatum().day() << "} \\newline";
						*stream << " {\\bf /" <<  ke->getDatum().month() << "} ";
						itt++;
					}
					if(j<(p_size-1)) *stream << "&";
			}
			*stream << "\\\\ \n \\hline \n";
	
			//list<schueler*> *list_sch = kb->getKlasse()->getSchueler();
			for(list<schueler*>::iterator it=list_sch->begin(); it != list_sch->end(); it++){
				schueler *s = (*it);
				itt = list_kbe->begin();
				for(int j=0; j<offset; j++) itt++;
				for(int j=0; j<p_size; j++){
					if(itt != list_kbe->end()){
						krusbucheintrag *ke = (*itt);
						if(stundenplaneintrag *se = ke->getStundenplanEintrag()){
							if(se->getFehlzeit(s)){
								*stream << " x ";
							} else  {
								*stream << " ";
							}
						} else {
							*stream << " ? ";
						}
						itt++;
					}
					if(j<(p_size-1))  *stream << "&";
				}
				*stream << "\\\\ \n \\hline  \n ";
			}
			for(int k=26-n_schueler; k>0; k--){
				for(int j=0; j<(p_size-1); j++){
					*stream << " &"; 
				}
				*stream << " \\\\ \\hline \n";
			}

			*stream << "\\end{tabular} \n \\newpage \n\n";
		} // End Fehlzeiten-Tabellen


		
		*stream << "\\renewcommand{\\arraystretch}{3.2} \n";

		list<krusbucheintrag*>::iterator it = list_kbe->begin();

		int page_count = 0;
		while(it != list_kbe->end()){
            *stream << "\n \\newpage \n \n \\titlebox{ " << kb->getName().c_str() ;
			if(page_count > 0){
				*stream << " (Seite " << page_count +1 << ")  ";
			}
			*stream << "} \n";
			*stream << "\\begin{tabular}{|c|c|p{7.9cm}|p{6cm}|} \n \\hline \n {\\bf Datum} & {\\bf Stunde} & {\\bf Thema} & {\\bf Bemerkung} \\\\ \n \\hline \n ";
			list<krusbucheintrag*> *list_kbe = kb->getEintraege();
			
			int item_count =0;
			while((it != (list_kbe->end())) && (item_count < 16)){
				krusbucheintrag *kbe = (*it);
                *stream << kbe->getDatum().toString("ddd dd.MM") << " & ";
                if(kbe->getStundenplanEintrag()){
                    *stream <<  kbe->getStundenplanEintrag()->getNrStunde();
                } else {
                    *stream << "??";
                }
                *stream << " & " <<  kbe->getEintrag().c_str() << " & " << kbe -> getBemerkung().c_str() << " \\\\ \n \\hline \n";
				item_count++;
				it++;
			}

			*stream << "\\end{tabular}\n\n ";	
			page_count++;
		}
		
		
	}	
}

/*!
    \fn LatexOutput::write(list<fehlzeiten*> *lf)
 */
void LatexOutput::write(list<fehlzeit*> *lf)
{
    if(stream){
	//Tutor map aufbauen
    std::map<string,list<fehlzeit* >* > map_tutor;
	for(list<fehlzeit*>::iterator it=lf->begin(); it!=lf->end(); it++){
		fehlzeit *fz = *it;
		if(schueler *s=fz->getSchueler()){
			string tutor = s->getTutor();
			list<fehlzeit*> *l_tutor = map_tutor[tutor];
			if(!l_tutor){
				l_tutor = new list<fehlzeit*>();
				map_tutor[tutor]=l_tutor;
			}
			l_tutor->push_back(fz);
		}
	}
	
    QString dS=QString("\\definecolor{draft}{rgb}{.1,.2,.8}\n");
    dS=dS.append("\\textcolor{draft}{\\Large\\bf\\sf\n");

    for(std::map<string,list<fehlzeit*>*>::iterator it = map_tutor.begin(); it != map_tutor.end(); it++){
		string tutor = it->first;
		list<fehlzeit*>  *l = it->second;
        std::map<stundenplaneintrag*,list<fehlzeit*>* > map_se;
        for(list<fehlzeit*>::iterator itt=l->begin(); itt!=l->end(); itt++){
            stundenplaneintrag *se=(*itt)->getStundenplaneintrag();
            list<fehlzeit*> *lse=map_se[se];
            if(!lse){
                lse=new list<fehlzeit*>();
                map_se[se]=lse;
            }
            lse->push_back((*itt));
        }



        for(std::map<stundenplaneintrag*,list<fehlzeit*>* >::iterator itt=map_se.begin(); itt!=map_se.end(); itt++){
            stundenplaneintrag *se = itt->first;
            list<fehlzeit*> *l=itt->second;
            if(! l->empty()){
                QString d=se->getDatum().toString();
                int n=se->getNrStunde()-1;
                int dow=se->getDatum().dayOfWeek()-1;

                dS=dS.append("\\begin{pspicture}(9,13)\n");
                dS=dS.append("\\rput(4.5,6.5){\\includegraphics{/home/mopp/schule/Stundenplaner/form-fz.ps} }");
                dS=dS.append("\\rput[l](2.0,12.0){Dirks}\n");
                dS=dS.append("\\rput[l](6.5,10.7){").append(tutor.c_str()).append("}\n");
                dS=dS.append("\\rput[l](2.0,10.6){").append(d).append("}\n");
                dS=dS.append("\\rput[l](%1,9.6){X}\n").arg(1.6+1.2*dow);
                dS=dS.append("\\rput[l](%2,8.6){X}\n").arg(1.0+0.8*n);


                float ys=6.9;

                for(list<fehlzeit* >::iterator itfz = l->begin(); itfz != l->end(); itfz++){
                    fehlzeit *fz = (*itfz);
                    schueler *s = fz->getSchueler();
                    if(s){
                        ys=ys-0.9;
                        dS=dS.append("\\rput[l](2.0,%1){").arg(ys);
                        dS=dS.append(s->getVorname().c_str()).append(" ").append(s->getNachname().c_str()).append("}\n");
                    }
                }
                dS=dS.append("\\end{pspicture}\\qquad\n");


            }
		}

	}
	
    dS=dS.append("}\n");
    *stream << dS;

    }
}


/*!
    \fn LatexOutput::punkteToNote(int n)
 */
QString LatexOutput::punkteToNote(int n)
{
    if(n==15) return QString("1+");	
    else if(n==14) return QString("1");
    else if(n==13) return QString("1-");
    else if(n==12) return QString("2+");
    else if(n==11) return QString("2");
    else if(n==10) return QString("2-");
    else if(n==9) return QString("3+");
    else if(n==8) return QString("3");
    else if(n==7) return QString("3-");
    else if(n==6) return QString("4+");
    else if(n==5) return QString("4");
    else if(n==4) return QString("4-");
    else if(n==3) return QString("5+");
    else if(n==2) return QString("5");
    else if(n==1) return QString("5-");
    else if(n==0) return QString("6");
    else return QString("?");
}

void LatexOutput::write_report(teilleistung *tl)
{
    qDebug("LatexOutput::write -- teilleistung");
    if(stream){
        QString fach("Unbekannt");
        QString kurs("Unbekannt");
        QString lehrer("Dirks");
        int klassenstufe=0;
        if(klasse *kl=tl->getKlasse()){
            fach=kl->getFach().c_str();
            klassenstufe = kl->getJahrgangsstufe();
            kurs=kl->getKursnummer().c_str();
        }
        QString dS=QString("\\definecolor{draft}{rgb}{.1,.2,.8}\n");
        dS=dS.append("\\textcolor{draft}{\\Large\\bf\\sf\n");
        dS=dS.append("\\begin{pspicture}(18,27)\n");
        dS=dS.append("\\rput(8.5,13){\\includegraphics{/home/mopp/schule/formular-klausur.ps} }");
        dS=dS.append(QString("\\rput(3,23.4){%1}\n\\rput(3,22.5){%2}\n").arg(fach).arg(lehrer));
        dS=dS.append(QString("\\rput(11.8,23.4){%1}\n\\rput(14.8,23.4){%2}").arg(klassenstufe).arg(kurs));
        dS=dS.append(QString("\\rput(4.4,21.5){%1}\n").arg(tl->getDatum().toString(Qt::SystemLocaleShortDate)));
        int all=tl->getNoten()->size();
        dS=dS.append(QString("\\rput(13,22.4){%1}\n").arg(all));
        int mis=tl->getAnzahl(-1);
        dS=dS.append(QString("\\rput(13,21.5){%1}\n").arg(mis));

        int sum=0;
        int ges=0;
        for(int i=1; i<=6; i++){
            int n=tl->getAnzahlNote(i);
            ges+=n;

            sum+=n*i;
            dS=dS.append(QString("\\rput(%1,18.6){%2}\n").arg(i-1+.4).arg(n));
        }
        dS=dS.append(QString("\\rput(13,20.3){%L1}\n").arg(sum*1.0/ges,0,'f',2));
        dS=dS.append("\\end{pspicture}\n");
        dS=dS.append("}\n");
        *stream << dS;
    } else {qDebug("LatexOutput::write_report(teilleistung) - kein stream !?");}
}

/*!
    \fn LatexOutput::write(teilleistung *tl)
 */
void LatexOutput::write(teilleistung *tl)
{
   qDebug("LatexOutput::write -- teilleistung");
   if(stream){
    QString dS=QString("\\begin{center} {\\bf \n %1 -- %2\\\\ \n Ergebnis\\\"ubersicht}\\\\[.5cm] \n\n").arg(tl->getName().c_str()).arg(tl->getKlasse()->getName().c_str());
	int all=tl->getNoten()->size();
	int mis=tl->getAnzahl(-1);
	dS=dS.append(QString("Von %1 Sch\\\"ulern: %2 geschrieben, %3 gefehlt \\\\[.5cm] \n").arg(all).arg(all-mis).arg(mis));
	dS=dS.append("\\begin{description}\n");
	// noten
	int sum=0;
	int ges=0;
	dS=dS.append("\\item[Noten]~\\\\[.5cm]\n");
	dS=dS.append("\\begin{tabular}{|c|c|c|c|c|c|} \n \\hline \n");
	for(int i=1;i<=5;i++){
		dS=dS.append(QString("%1  & ").arg(i)); 
	}
	dS=dS.append("6 \\\\ \\hline \n");
	for(int i=1; i<=5; i++){
		int n=tl->getAnzahlNote(i);
		ges+=n;
		sum+=n*i;
		dS=dS.append(QString("%1 & ").arg(tl->getAnzahlNote(i)));
	}
	int n=tl->getAnzahlNote(6);
	ges+=n;
	sum+=n*6;
	dS=dS.append(" %1 \\\\ \n \\hline \n").arg(n);
	dS=dS.append("\\end{tabular}\n\n");
	dS=dS.append(QString("{\\bf Durchschnitt: %1}\n").arg(sum*1.0/ges));
	//punkte
	sum=0;
	ges=0;
	dS=dS.append("\\item[Punkte]~\\\\[.5cm]\n");
	dS=dS.append("\\begin{tabular}{|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|} \n \\hline \n");
	for(int i=15;i>0;i--){
		dS=dS.append(QString("%1  & ").arg(i)); 
	}
	dS=dS.append("0 \\\\ \\hline \n");
	for(int i=15; i>0; i--){
		int n=tl->getAnzahl(i);
		ges+=n;
		sum+=n*i;
		dS=dS.append(QString("%1 & ").arg(n));

	}
	n=tl->getAnzahlNote(0);
	ges+=n;
	sum+=n*0;
	dS=dS.append(QString(" %1 \\\\ \n \\hline \n").arg(n));
	dS=dS.append("\\end{tabular}\n\n");
	dS=dS.append(QString("{\\bf Durchschnitt: %1}\n").arg(sum*1.0/ges));
	

	dS=dS.append("\\end{description} \n \\end{center}\n");

	dS=dS.append("\\newpage");

    dS=dS.append("\\begin{center} {\\bf \n %1 -- %2\\\\ \n Ergebnis\\\"ubersicht}\\\\[.5cm] \n\n").arg(tl->getName().c_str()).arg(tl->getKlasse()->getName().c_str());

	dS=dS.append("\\begin{tabular}{|c|c|c|}\n \\hline \\\\ \n");
	dS=dS.append("{\\bf Vorname} & {\\bf Vorname} & {\\bf Punkte}\\\\ \\hline \n");
	list<schueler*> *listSchueler = tl->getKlasse()->getSchueler();
	for(list<schueler*>::iterator it=listSchueler->begin(); it != listSchueler->end(); it++){
		schueler *s=(*it);
		int p = tl->getNote(s)->getPunkte();
        dS.append(QString("%1 & %2 & %3 \\\\\\hline \n").arg(s->getNachname().c_str()).arg(s->getVorname().c_str()).arg(p));
	}
	dS=dS.append("\n \\end{tabular}\n");
	dS=dS.append("\\end{center}");
    *stream << dS;
  } else {qDebug("LatexOutput::write(teilleistung) - kein stream !?");}
}
