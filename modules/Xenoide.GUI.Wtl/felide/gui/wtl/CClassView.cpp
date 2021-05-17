
#include "CClassView.hpp"

#include "../../../resource.h"

namespace felide {
    CClassView::CClassView() {

    }


    CClassView::~CClassView() {

    }


    int CClassView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
        // setup imagelist
        HBITMAP b1 = bitmap1.LoadBitmapA(IDB_BITMAP3);
        HBITMAP b2 = bitmap2.LoadBitmapA(IDB_BITMAP2);
        HBITMAP b3 = bitmap3.LoadBitmapA(IDB_BITMAP4);

        int image1 = imageList.Add(bitmap1);
        int image2 = imageList.Add(bitmap2);
        int image3 = imageList.Add(bitmap3);

        // setup treeview
        RECT clientRect;
        this->GetClientRect(&clientRect);

        treeView.Create(m_hWnd, &clientRect, "",  TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | WS_VISIBLE | WS_CHILD);
        treeView.SetImageList(imageList, TVSIL_NORMAL);
        
        const HTREEITEM rootItem = treeView.InsertItem("namespace", 0, 0, nullptr, nullptr);
        const DWORD style = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;

        TVINSERTSTRUCT insertStruct = {};

        insertStruct.hParent = rootItem;
        insertStruct.item.mask = style;
        insertStruct.item.pszText = "Class1";
        insertStruct.item.iImage = 1;
        insertStruct.item.iSelectedImage = 1;
        treeView.InsertItem(&insertStruct);

        insertStruct.hParent = rootItem;
        insertStruct.item.mask = style;
        insertStruct.item.pszText = "Class2";
        insertStruct.item.iImage = 1;
        insertStruct.item.iSelectedImage = 1;
        treeView.InsertItem(&insertStruct);

        insertStruct.hParent = rootItem;
        insertStruct.item.mask = style;
        insertStruct.item.pszText = "Function1";
        insertStruct.item.iImage = 2;
        insertStruct.item.iSelectedImage = 2;
        treeView.InsertItem(&insertStruct);

        return 0;
    }
}
