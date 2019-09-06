// GLDisplayContext.cpp: implementation of the CGLDisplayContext class.
//
//////////////////////////////////////////////////////////////////////

#include "VGLDisplayContext.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VGLDisplayContext::VGLDisplayContext()
{
}

VGLDisplayContext::VGLDisplayContext(VirmacDocument* pDoc)
{
    display = new ListOfVGLObject;
    erase = new ListOfVGLObject;
    select = new ListOfVGLObject;
    selListIter.SetList(select);
    selListIter.Init();
    ptrDoc = pDoc;
    viewBox.SetLimits(-1, 1, -1, 1, -1, 1);
    mouseSensitivity = 5; //5 pixels sensitivity
}

VGLDisplayContext::~VGLDisplayContext()
{
    if(!display->IsEmpty())
        display->Clear();
    if(!erase->IsEmpty())
        erase->Clear();
    if(!select->IsEmpty())
        select->Clear();
    delete display;
    delete erase;
    delete select;
}

void VGLDisplayContext::Display(VGLObject* aO)
{
    if(aO == NULL)
        return;
    //CGLObject* O = aO->Copy();
    if(display->IsEmpty())
        viewBox = aO->GetBoundingBox();
    else
        viewBox.AddBox(aO->GetBoundingBox());
    display->Append(aO);
}

void VGLDisplayContext::RefreshVolume()
{
    viewBox.SetLimits(-1, 1, -1, 1, -1, 1);
    ListIteratorOfListOfVGLObject listIter(display);
    for(listIter.Init(); listIter.More(); listIter.Next())
    {
        VGLObject* pObj = (VGLObject*)listIter.Current();
        BoundingBox b = pObj->GetBoundingBox();
        viewBox.AddBox(b);
    }
}

void VGLDisplayContext::Erase(VGLObject* aO)
{
    erase->Append(display->Remove(aO));
}

void VGLDisplayContext::DisplayAll()
{
    ListIteratorOfListOfVGLObject listIter(erase);
    for(listIter.Init(); listIter.More(); listIter.Next())
    {
        VGLObject* eO = listIter.Current();
        if(display->IsEmpty())
            viewBox = eO->GetBoundingBox();
        else
            viewBox.AddBox(eO->GetBoundingBox());
        display->Append(eO);
        listIter.SetCurrent(0);
    }
    erase->Clear();
}

void VGLDisplayContext::DisplaySelected()
{
    if(!HasSelected())
        return;
    EraseAll();
    ListIteratorOfListOfVGLObject listIterD(erase);
    ListIteratorOfListOfVGLObject listIterSel(select);
    VGLObject* eO = 0, *sO = 0;
    for(listIterSel.Init(); listIterSel.More(); listIterSel.Next())
    {
        sO = listIterSel.Current();
        for(listIterD.Init(); listIterD.More(); listIterD.Next())
        {
            eO = listIterD.Current();
            if(eO->GetObjID() == sO->GetObjID())
                break;
        }
        if(display->IsEmpty())
            viewBox = eO->GetBoundingBox();
        else
            viewBox.AddBox(eO->GetBoundingBox());
        display->Append(erase->Remove(eO));
    }
    EmptySelection();
}

void VGLDisplayContext::EraseAll()
{
    ListIteratorOfListOfVGLObject listIter(display);
    for(listIter.Init(); listIter.More(); listIter.Next())
    {
        erase->Append(listIter.Current());
        listIter.SetCurrent(0);
    }
    display->Clear();
}

void VGLDisplayContext::EraseSelected()
{
    if(!HasSelected())
        return;
    ListIteratorOfListOfVGLObject listIterD(display);
    ListIteratorOfListOfVGLObject listIterSel(select);
    VGLObject* eO = 0, *sO = 0;
    for(listIterSel.Init(); listIterSel.More(); listIterSel.Next())
    {
        sO = listIterSel.Current();
        for(listIterD.Init(); listIterD.More(); listIterD.Next())
        {
            eO = listIterD.Current();
            if(eO->GetObjID() == sO->GetObjID())
                break;
        }
        Erase(eO);
    }
    EmptySelection();
    viewBox.SetLimits(-1,1,-1,1,-1,1);
    for(listIterD.Init(); listIterD.More(); listIterD.Next())
        viewBox.AddBox(listIterD.Current()->GetBoundingBox());
}

void VGLDisplayContext::DeleteAll()
{
    if(!display->IsEmpty())
        display->Clear();
    if(!erase->IsEmpty())
        erase->Clear();
    EmptySelection();
    viewBox.SetLimits(-1, 1, -1, 1, -1, 1);
}

void VGLDisplayContext::DeleteSelected()
{
    if(!HasSelected())
        return;
    ListIteratorOfListOfVGLObject listIterD(display);
    ListIteratorOfListOfVGLObject listIterSel(select);
    VGLObject* eO = 0, *sO = 0;
    for(listIterSel.Init(); listIterSel.More(); listIterSel.Next())
    {
        sO = listIterSel.Current();
        for(listIterD.Init(); listIterD.More(); listIterD.Next())
        {
            eO = listIterD.Current();
            if(eO->GetObjID() == sO->GetObjID())
                break;
        }
        delete display->Remove(eO);
    }
    EmptySelection();
    viewBox.SetLimits(-1,1,-1,1,-1,1);
    for(listIterD.Init(); listIterD.More(); listIterD.Next())
        viewBox.AddBox(listIterD.Current()->GetBoundingBox());
}

void VGLDisplayContext::DeletePoints()
{
    EmptySelection();
    ListIteratorOfListOfVGLObject listIterD(display);
    VGLObject* eO = 0;
    for(listIterD.Init(); listIterD.More(); listIterD.Next())
    {
        eO = listIterD.Current();
        if(eO->IsOfType(GLPOINT))
            break;
    }
    delete display->Remove(eO);
}

void VGLDisplayContext::Render(const GLDisplayMode& mode)
{
    if(IsEmpty())
        return;
    VGLObject* O;

    // Initialize the names stack
    //glInitNames();  commented out for application specific use
    //glPushName(0);  commented out for application specific use
    ListIteratorOfListOfVGLObject listIter(display);
    for(listIter.Init(); listIter.More(); listIter.Next())
    {
        O = listIter.Current();
        if(O && !O->IsHidden())
        {
            //glLoadName(O->GetObjID());       commented out for application specific use
            O->Display(O->GetDisplayMode());
        }
    }
    listIter.SetList(select);
    for(listIter.Init(); listIter.More(); listIter.Next())

    {
        O = listIter.Current();
        if(O && !O->IsHidden())
            O->Hilight(mode);
    }
}

bool VGLDisplayContext::Select(VirmacGLView* aView, const int& x, const int& y)
{
    bool res = false;
    VGLObject* O = 0;
    unsigned long int id = aView->ProcessSelection(x, y, mouseSensitivity);
    if(id)
        res = true;
    else
    {
        EmptySelection();
        return false;
    }
    ListIteratorOfListOfVGLObject listIter(display);
    for(listIter.Init(); listIter.More(); listIter.Next())
    {
        O = listIter.Current();
        if(O)
        {
            if(id == O->GetObjID())
            {
                if(!IsSelected(O))
                {
                    select->Clear();
                    AddToSelection(O);
                }
                else
                    RemoveSelection(O);
            }
        }
    }
    return res;
}

bool VGLDisplayContext::MultiSelect(VirmacGLView* aView, const int& x, const int& y)
{
    bool res = false;
    VGLObject* O = 0;
    unsigned long int id = aView->ProcessSelection(x, y, mouseSensitivity);
    if(id)
        res = true;
    ListIteratorOfListOfVGLObject listIter(display);
    for(listIter.Init(); listIter.More(); listIter.Next())
    {
        O = listIter.Current();
        if(O)
        {
            if(id == O->GetObjID())
            {
                if(!IsSelected(O))
                    AddToSelection(O);
                else
                    RemoveSelection(O);
            }
        }
    }
    return res;
}

bool VGLDisplayContext::SweepSelect(VirmacGLView* aView, const QRect& swRect)
{
    bool res = false;
    VGLObject* O = 0;
    unsigned long int *id = new unsigned long int[100];
    int no_of_objs = aView->ProcessSweepSelection(swRect, id);
    if(no_of_objs)
        res = true;
    ListIteratorOfListOfVGLObject listIter(display);
    for(listIter.Init(); listIter.More(); listIter.Next())
    {
        O = listIter.Current();
        if(O)
        {
            for(int i = 0; i < no_of_objs; i++)
            {
                if(id[i] == O->GetObjID())
                    AddToSelection(O);
            }
        }
    }
    delete [] id;
    return res;
}

bool VGLDisplayContext::IsEmpty() const
{
    return (display->IsEmpty() && erase->IsEmpty());
}

bool VGLDisplayContext::IsDisplayed(const VGLObject* O) const
{
    if(O == NULL)
        return false;
    ListIteratorOfListOfVGLObject li(display);

    return li.IsFound(O);
}

bool VGLDisplayContext::IsErased(const VGLObject* O) const
{
    if(O == NULL)
        return false;
    ListIteratorOfListOfVGLObject li(erase);
    return li.IsFound(O);
}

bool VGLDisplayContext::IsSelected(const VGLObject* O) const
{
    bool b = false;
    if(O == NULL)
        return false;
    ListIteratorOfListOfVGLObject li(select);
    for(li.Init(); li.More(); li.Next())
    {
        if(O->GetObjID() == li.Current()->GetObjID())
        {
            b = true;
            break;
        }
    }
    return b;
}

bool VGLDisplayContext::IsAllDisplayed() const
{
    return erase->IsEmpty();
}

bool VGLDisplayContext::IsAllErased() const
{
    return display->IsEmpty();
}

bool VGLDisplayContext::HasSelected() const
{
    return !select->IsEmpty();
}

void VGLDisplayContext::InitSelected() const
{
    selListIter.Init();
}

bool VGLDisplayContext::MoreSelected() const
{
    return selListIter.More();
}

void VGLDisplayContext::NextSelected() const
{
    selListIter.Next();
}

VGLObject* VGLDisplayContext::CurrentSelected() const
{
    VGLObject* sO = selListIter.Current();
    VGLObject* O = 0;
    ListIteratorOfListOfVGLObject listIter(display);
    for(listIter.Init(); listIter.More(); listIter.Next())
    {
        if(sO->GetObjID() == listIter.Current()->GetObjID())
        {
            O = listIter.Current();
            break;
        }
    }
    return O;
}

//Private
void VGLDisplayContext::AddToSelection(const VGLObject* O)
{
    select->Append(O->Copy());
}

void VGLDisplayContext::RemoveSelection(const VGLObject* O)
{
    ListIteratorOfListOfVGLObject listIter(select);
    for(listIter.Init(); listIter.More(); listIter.Next())
    {
        if(O->GetObjID() == listIter.Current()->GetObjID())
        {
            delete select->Remove(listIter.Current());
            break;
        }
    }
}

void VGLDisplayContext::EmptySelection()
{
    if(!select->IsEmpty())
        select->Clear();
}
