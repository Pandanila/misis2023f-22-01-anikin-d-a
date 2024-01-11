**Тема:** форматы файлов - бинарные – DICOM  
**ФИО:** Аникин Данила Андреевич  
**Дата:** 29.12.2023  
**Digital Imaging and Communications in Medicine (DICOM)** – стандарт обработки, 
хранения, передачи, печати и визуализации медицинских изображений.

### Цель создания  
До создания DICOM в сфере медицинских исследований отсутствовал общепринятый **стандарт** работы с цифровыми изображениями. Это вынуждало пользователей иметь дело с множеством форматов данных и преобразовывать данные из одного формата в другой.  

**Стандарт** DICOM определяет:  

**файловый уровень** — DICOM File (DICOM-файл) — объектный файл с теговой организацией для представления кадра изображения (или серии кадров) и сопровождающей или управляющей информации (в виде DICOM-тегов);  

**сетевой (коммуникационный) уровень** — DICOM Network Protocols (сетевой DICOM-протокол) — для передачи DICOM-файлов и управляющих DICOM-команд по сетям с поддержкой TCP/IP. (Larobina, 2023)  


### Терминология

**Информационная модель DICOM**

Пациент (patient) → Исследование (study) → Серия (series) → Изображение (кадр 
или серия кадров, image)

**Service Class User** – устройство-клиент, которое инициирует запрос

**Service Class Provider** – устройство, предоставляющее сервис

**Information Object Definition** – объектно-ориентированная абстрактная модель данных, используемая для указания информации об объектах реального мира. IOD не представляет собой конкретный экземпляр объекта реального мира, а скорее класс объектов реального мира, которые имеют одни и те же свойства.  
Например, MR Image – Объект МРТ-снимков.

**Service Group** – набор команд, которые можно запрашивать у SCP.

Примеры команд: Print (Печать), Storage (Хранение), Query/Retrieve (Получение 
объекта). 

**Service Object Pair** – комбинация команды (Service Group) и объекта (Information Object Definition), с которым эта команда будет выполняться.  
Например, SOP Class “MR Image Storage” = Storage + MR Image.

**Application Entities** – отдельный сервис DICOM, узел сети DICOM. (Medema)

![image](https://github.com/Pandanila/misis2023f-22-01-anikin-d-a/assets/97802843/ecacd8d6-979c-4c48-8016-1536cd4ddea2)


### Формат файлов DICOM

Формат файла DICOM предоставляет средства для инкапсуляции в файл набора данных, представляющего экземпляр SOP, связанный с IOD DICOM. Как показано на рисунке, поток байтов набора данных помещается в файл после метаинформации файла DICOM. Каждый файл содержит один экземпляр SOP.

![image](https://github.com/Pandanila/misis2023f-22-01-anikin-d-a/assets/97802843/39aca6ea-d50e-4eb6-b28b-1f5a4d00017b)

**Метаинформация файла** включает в себя идентификационную информацию об инкапсулированном наборе данных. Этот заголовок состоит из 128-байтовой преамбулы файла, за которой следует 4-байтовый префикс DICOM, за которым следуют метаэлементы файла, показанные в таблице. Этот заголовок должен присутствовать в каждом файле DICOM. (dicom.nema.org)

![image](https://github.com/Pandanila/misis2023f-22-01-anikin-d-a/assets/97802843/3fba714a-a265-4010-92cd-44cabfff1197)
![image](https://github.com/Pandanila/misis2023f-22-01-anikin-d-a/assets/97802843/f0ce3d1e-11fe-4b64-84da-6c30855b4e31)
![image](https://github.com/Pandanila/misis2023f-22-01-anikin-d-a/assets/97802843/584124a2-166b-4872-9b77-7c5112b0a269)

### Структура IOD

![image](https://github.com/Pandanila/misis2023f-22-01-anikin-d-a/assets/97802843/cad154a9-12ea-4b7a-99c1-bc9de39ecf28)

**Атрибуты** IOD описывают свойства экземпляра реального объекта. Связанные атрибуты сгруппированы в **модули**, которые представляют более высокий уровень семантики.

![image](https://github.com/Pandanila/misis2023f-22-01-anikin-d-a/assets/97802843/79fb7ffd-b182-4b44-9da5-a2d17abd5671)
![image](https://github.com/Pandanila/misis2023f-22-01-anikin-d-a/assets/97802843/3cb3d00b-735f-4579-9085-09bbcddee461)

**Тэг** – Определяет ключ атрибута/элемента данных

**Представление значения (VR)** – Определяет тип данных, используемый для кодирования значения (есть таблица типов для формата DICOM, например, PN – Person Name)

**Кратность значений (VM)** – Определяет, сколько значений может быть в атрибуте

**Модуль** – Архитектурное удобство, логическая группа атрибутов, относящихся к общей теме.

![image](https://github.com/Pandanila/misis2023f-22-01-anikin-d-a/assets/97802843/0e4fdaed-e7d1-4dd5-8780-c7208ef4abd3)

**Type:** 1 – обязательный, 2 – может быть пустым, если неизвестно, 3 – необязательный, 1С или 2С – условный.

### Работа с DICOM в C++

Наиболее оптимальный способ работать со стандартом DICOM - использование специализированных C++ библиотек. Например, это библиотека DCMTK.
В DCMTK входит программное обеспечение:
*	для проверки, создания и преобразования файлов изображений DICOM
*	для работы с носителями информации
*	для отправки и получения изображений через сетевое соединение

Пример создания dicom-файла с помощью библиотеки DCMTK приведен в прикрепленном файле.

```сpp
#include <iostream>
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmdata/libi2d/i2d.h"
#include "dcmtk/dcmdata/libi2d/i2djpgs.h"
#include "dcmtk/dcmdata/libi2d/i2dplsc.h"
#include "dcmtk/dcmdata/dctk.h"

void createDicomImage() {
    char uid[100];
    I2DImgSource* inputPlug = new I2DJpegSource();
    I2DOutputPlug* outPlug = new I2DOutputPlugSC();
    Image2Dcm i2d;
    E_TransferSyntax writeXfer;
    DcmDataset* resultDset = NULL;
//uid будет использоваться для создания uid для экземпляра SOP.
//inputPlug имеет тип I2DJpegSource, который представляет собой реализацию I2DImgSource для анализа изображений JPEG и преобразования их в файлы DICOM.
//outPlug имеет тип I2DOutputPlugSC, который реализует преобразование изображений в файлы DICOM.
//i2d — переменная типа Image2Dcm, в которой реализованы утилиты для преобразования изображения в файл DICOM.
//writeXfer — это переменная типа E_TransferSyntax, которая состоит из перечислителя всех синтаксисов передачи DICOM, известных набору инструментов.
//resultDset — это переменная типа DcmDataset, который представляет собой класс, обрабатывающий формат набора данных DICOM.

    inputPlug->setImageFile("test.jpg");
    i2d.convert(inputPlug, outPlug, resultDset, writeXfer);
//настраиваем входное изображение для чтения с помощью inputPlug , а затем выполним преобразование изображения в DICOM
//с помощью функции преобразования i2d , которой в качестве входных параметров передается следующее:
//
//  1. inputPlug с изображением для конвертации.
//  2. outPlug для выполнения преобразования.
//
//А выходными параметрами ему передается следующее:
//
//  1. resultDset для хранения результирующего объекта DICOM.
//  2. writeXfer , чтобы сохранить синтаксис передачи.

    resultDset->putAndInsertString(DCM_PatientName, "Brandon Lara");
    resultDset->putAndInsertString(DCM_SOPClassUID, UID_SecondaryCaptureImageStorage);
    resultDset->putAndInsertString(DCM_SOPInstanceUID, dcmGenerateUniqueIdentifier(uid, SITE_INSTANCE_UID_ROOT));
// После этого объект resultDset будет состоять из объекта DICOM без изображения, но с ним.
// Этот объект типа DcmDataset предоставляет определенные функции для установки данных в нем.
// Используя эти же функции, имя пациента, идентификатор класса СОП
// и идентификатор экземпляра СОП будут установлены с помощью тестовых данных

    DcmFileFormat dcmff(resultDset);
    dcmff.saveFile("test.dcm", writeXfer, EET_ExplicitLength, EGL_recalcGL, EPD_noChange, OFstatic_cast(Uint32, 0), OFstatic_cast(Uint32, 0), EWM_fileformat);
// resultDset будет сохранен как файл DICOM (.dcm) в папке проекта.
// Для этого необходимо создать DcmFileFormat с этим resultDset,
// чтобы сохранить его с помощью функции сохранения DcmFileFormat .
// Параметры, начиная с третьего, стандартные для преобразования img в dcm
}

void loadDicom() {
    DcmFileFormat fileformat;
    OFCondition status = fileformat.loadFile("test.dcm");
    if (status.good())
    {
        OFString patientName;
        if (fileformat.getDataset()->findAndGetOFString(DCM_PatientName, patientName).good())
        {
            std::cout << "Patient's Name: " << patientName << std::endl;
        }
        else
            std::cerr << "Error: cannot access Patient's Name!" << std::endl;
    }
    else
        std::cerr << "Error: cannot read DICOM file (" << status.text() << ")" << syd::endl;
}

int main()
{
    createDicomImage();
    loadDicom();
}
```
