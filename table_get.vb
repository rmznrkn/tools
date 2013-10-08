Sub MacroTabloCikar()
    '
    ' MacroTabloCikar Macro
    '
    '
    ActiveWindow.ActivePane.VerticalPercentScrolled = 0
End Sub
Sub CopyAllTablesToNewDoc()

    Dim docSource As Document
    Dim docDest As Document
    Dim tbl As Table

    docSource = ActiveDocument
    docDest = Documents.Add

    For Each tbl In docSource.Tables
        tbl.Range.Copy()
        docDest.Paragraphs(docDest.Paragraphs.Count).Range.Paste()
        docDest.Range.InsertParagraphAfter()
    Next tbl

End Sub

Public Sub CopyTablesToNewDoc()
    Dim docOld As Document
    Dim rngDoc As Range
    Dim tblDoc As Table

    If ActiveDocument.Tables.Count >= 1 Then
        docOld = ActiveDocument
        rngDoc = Documents.Add.Range(Start:=0, End:=0)
        For Each tblDoc In docOld.Tables
            tblDoc()
            'With rngDoc
            '.Paste
            '.Collapse Direction:=wdCollapseEnd
            '.InsertParagraphAfter
            '.Collapse Direction:=wdCollapseEnd
            'End With
        Next
    End If
End Sub



Sub RetrieveTableItems()

    Dim oRow As Row
    Dim oCell As Cell
    Dim iRow As Row
    Dim iCell As Cell
    Dim sCellText As String
    Dim printText As String
    Dim docOld As Document
    Dim rngDoc As Range
    Dim oTable As Table
    Dim tHeader As Table
    Dim tDetail As Table
    Dim docDest As Document
    Dim strFilename As String
    
    Dim c1Name As String
    Dim c2Name As String
    Dim c3Name As String
    Dim c4Name As String
    Dim c5Name As String
    Dim msgtype As Integer
    Dim defineFieldMessage As Integer
    Dim writeTable As Integer
    Dim writeFieldDef As Integer
    Dim writeSecBoardFieldCode As Integer
    Dim writeOkRep As Integer
    Dim writeBadRep As Integer
    Dim cell1 As String
    Dim cell2 As String
    Dim cell3 As String
    Dim cell4 As String
    Dim hold As String
    Dim strMsgType As String

    Dim intLogFile As Integer
    Dim intX As Integer
    Dim autoDefCnt As Integer
    Dim autoDefCnt1 As Integer
    Dim c1Found As Integer
    Dim c2Found As Integer
    Dim c3Found As Integer
    Dim c4Found As Integer
    Dim reqRep As Integer
    Dim messageFound As Integer
    Dim messageCount As Integer
    Dim intRowCnt As Integer
    Dim intColCnt As Integer
    Dim comesFromCall As Integer
    Dim tableCount As Integer

    Set docOld = ActiveDocument
    'strFilename = "C:\Users\ramazan.arikan\Desktop\viop_api_doc\viop\viop_api_doc\messages.xml"
    strFilename = "C:\Users\ramazan.arikan\Documents\eclipse_workspace\ssay\wtables.xml"
    intLogFile = FreeFile()
    Open strFilename For Output As #intLogFile
    On Error GoTo ErrorHandler
    Debug.Print (" Start of program ")
    tableCount = 0
    msgtype = 0
    writeTable = 0
    autoDefCnt = 0
    autoDefCnt1 = 0
    If ActiveDocument.Tables.Count >= 1 Then
        Debug.Print ("process started")
        For Each oTable In docOld.Tables
            tableCount = tableCount + 1
            Debug.Print ("table." & CStr(messageCount))
            c1Found = 0
            c2Found = 0
            c3Found = 0
            c4Found = 0
            writeTable = 0
            writeFieldDef = 0
            writeSecBoardFieldCode = 0
            writeOkRep = 0
            writeBadRep = 0
            For Each oRow In oTable.Rows
                'typespec table search
                If oRow.Cells.Count = 2 Then
                    cell1 = oRow.Cells(1).Range
                    cell2 = oRow.Cells(2).Range
                    cell1 = Left$(cell1, Len(cell1) - 2)
                    cell2 = Left$(cell2, Len(cell2) - 2)
                    If cell1 = "Position" And cell2 = "Meaning" Then
                        writeTable = 1
                    End If
                    If cell1 = "Field Hint" And cell2 = "Description" Then
                        writeOkRep = 1
                    End If
                    If cell1 = "Messages" And cell2 = "Code" Then
                        writeBadRep = 1
                    End If
                End If
                If oRow.Cells.Count = 3 Then
                    cell1 = oRow.Cells(1).Range
                    cell2 = oRow.Cells(2).Range
                    cell3 = oRow.Cells(3).Range
                    cell1 = Left$(cell1, Len(cell1) - 2)
                    cell2 = Left$(cell2, Len(cell2) - 2)
                    cell3 = Left$(cell3, Len(cell3) - 2)
                    If cell1 = "Sectors" And cell2 = "Markets" And cell3 = "Boards" Then
                        writeTable = 1
                    End If
                    If cell1 = "Constant" And cell2 = "Length in Bytes" And cell3 = "Description" Then
                        writeFieldDef = 1
                    End If
                End If
                If oRow.Cells.Count > 3 Then
                    cell1 = oRow.Cells(1).Range
                    cell2 = oRow.Cells(2).Range
                    cell3 = oRow.Cells(3).Range
                    cell4 = oRow.Cells(4).Range
                    cell1 = Left$(cell1, Len(cell1) - 2)
                    cell2 = Left$(cell2, Len(cell2) - 2)
                    cell3 = Left$(cell3, Len(cell3) - 2)
                    cell4 = Left$(cell4, Len(cell4) - 2)
                    If cell1 = cell2 And cell2 = cell3 And cell3 = cell4 Then
                        If cell1 = "OperatorMsg" Then
                            msgtype = 1
                            strMsgType = "Operator"
                        End If
                        If cell1 = "QueryRequest" Then
                            msgtype = 2
                            strMsgType = "Query"
                        End If
                        If cell1 = "Transaction" Then
                            msgtype = 3
                            strMsgType = "Transaction"
                        End If
                        If cell1 = "TransactionReply" Then
                            msgtype = 4
                            strMsgType = "TransactionReply"
                        End If
                        If cell1 = "Broadcast" Then
                            strMsgType = "Broadcast"
                            msgtype = 5
                        End If
                        If cell1 = "FieldDef" Then
                            strMsgType = "FieldDef"
                            msgtype = 6
                        End If
                    End If
                    If cell1 = "SectypeId" And cell2 = "BoardId" And cell3 = "SecId" And cell4 = "Meaning" Then
                        writeTable = 1
                    End If
                    If cell1 = "Code" Then
                        writeSecBoardFieldCode = 0
                    End If
                    If cell1 = "Code" And cell2 = "Field" And cell3 = "Type" And cell4 = "Width" Then
                        writeSecBoardFieldCode = 0
                    End If
                End If

                If writeTable <> 0 Then
                    GoTo writeTableX
                End If
                If writeFieldDef <> 0 Then
                    GoTo writeFieldDefX
                End If
                If writeSecBoardFieldCode <> 0 Then
                    GoTo writeSecBoardFieldCodeX
                End If
                If writeOkRep <> 0 Then
                    GoTo writeTableX
                End If
                If writeBadRep <> 0 Then
                    GoTo writeTableX
                End If

                For Each oCell In oRow.Cells
                    sCellText = oCell.Range
                    sCellText = Left$(sCellText, Len(sCellText) - 2)
                    If sCellText = "Field Name" Then
                        c1Found = 1
                        c1Name = sCellText
                    End If
                    If sCellText = "Mand." Then
                        c2Found = 1
                        c2Name = sCellText
                    End If
                    If sCellText = "Length" Then
                        c3Name = sCellText
                        c3Found = 1
                    End If
                    If sCellText = "Description" Then
                        c4Name = sCellText
                        c4Found = 1
                    End If
                    If c1Found <> 0 And c2Found <> 0 And c3Found <> 0 And c4Found <> 0 Then
                        comesFromCall = 1
                        Set tDetail = oTable
                        GoTo PrintTables
                    End If
                Next oCell
            Next oRow
            reqRep = 0
            writeTable = 1
            GoTo writeTableTITLE
ContinueToIterate:
            Set tHeader = oTable
GotoNextTable:
            comesFromCall = 0
        Next oTable
    End If

    writeTable = 0
    writeFieldDef = 0
    writeSecBoardFieldCode = 0
    writeOkRep = 0
    writeBadRep = 0
    
writeTableX:
    If writeTable <> 0 Then
        '/////////////////////////////////////////////////////
        printText = "<generalTable>"
    Print #intLogFile, printText; vbCr;
        intRowCnt = 0
        For Each iRow In oTable.Rows
            '----------------------
            If intRowCnt = 0 Then
                printText = "<definition>"
            End If
            If intRowCnt <> 0 Then
                printText = "<row>"
            End If
        Print #intLogFile, "  "; printText; vbCr;
            '----------------------
            intColCnt = 0
            For Each iCell In iRow.Cells
                '----------------------
                printText = "<column>"
            Print #intLogFile, "  "; "  "; printText;
                '----------------------
                sCellText = iCell.Range
                sCellText = Left$(sCellText, Len(sCellText) - 2)
                printText = sCellText
            Print #intLogFile, printText;
                '----------------------
                printText = "</column>"
            Print #intLogFile, printText; vbCr;
                '----------------------
                intColCnt = intColCnt + 1
            Next iCell
            '----------------------
            If intRowCnt = 0 Then
                printText = "</definition>"
            End If
            If intRowCnt <> 0 Then
                printText = "</row>"
            End If
        Print #intLogFile, "  "; printText; vbCr;
            '----------------------
            intRowCnt = intRowCnt + 1
        Next iRow
        printText = "</generalTable>"
    Print #intLogFile, printText; vbCr;
        '/////////////////////////////////////////////////////
        GoTo GotoNextTable
    End If
    
writeTableTITLE:
    If writeTable <> 0 Then
        '/////////////////////////////////////////////////////
        printText = "<table>"
        Print #intLogFile, printText;
        intRowCnt = 0
        For Each iRow In oTable.Rows
            intColCnt = 0
            For Each iCell In iRow.Cells
                '----------------------
                printText = "<c>"
                Print #intLogFile, "  "; printText;
                '----------------------
                sCellText = iCell.Range
                sCellText = Left$(sCellText, Len(sCellText) - 2)
                printText = sCellText
                Print #intLogFile, printText;
                '----------------------
                printText = "</c>"
                Print #intLogFile, printText;
                '----------------------
                intColCnt = intColCnt + 1
            Next iCell
            intRowCnt = intRowCnt + 1
        Next iRow
        printText = "</table>"
        Print #intLogFile, printText; vbCr;
        '/////////////////////////////////////////////////////
        writeTable = 0
        GoTo ContinueToIterate
    End If
    
writeFieldDefX:
    If writeFieldDef <> 0 Then

        '/////////////////////////////////////////////////////
        printText = "<message>"
    Print #intLogFile, printText; vbCr;
        ''''--------------
    Print #intLogFile, "  "; "<feature>"; vbCr;
    Print #intLogFile, "  "; "  "; "name="""; "category"; """"; vbCr; '"</name>"
    Print #intLogFile, "  "; "  "; "value="""; "fielddef"; """"; vbCr; ' "</value>"
    Print #intLogFile, "  "; "</feature>"; vbCr;
        ''''-------------
        intRowCnt = 0
        For Each iRow In oTable.Rows
            If intRowCnt <> 0 Then
                intColCnt = 0
                printText = "<field>"
                Print #intLogFile, "  "; printText; vbCr;
                For Each iCell In iRow.Cells
                    '----------------------
                    If intColCnt = 0 Then
                        printText = "name"
                    End If
                    If intColCnt = 1 Then
                        printText = "value"
                    End If
                    If intColCnt > 1 Then
                        printText = "description"
                    End If

                    ''''--------------
                Print #intLogFile, "  "; "  "; "<feature>"; vbCr;
                Print #intLogFile, "  "; "  "; "  "; "name="""; printText; """"; vbCr; '"</name>"


                    'Print #intLogFile, "  "; "  "; printText;
                    '----------------------
                    sCellText = iCell.Range
                    sCellText = Left$(sCellText, Len(sCellText) - 2)
                    printText = sCellText
                    'Print #intLogFile, printText;
                Print #intLogFile, "  "; "  "; "  "; "value="""; printText; """"; vbCr; ' "</value>"
                Print #intLogFile, "  "; "  "; "</feature>"; vbCr;
                    ''''-------------
                    '----------------------
                    If intColCnt = 0 Then
                        printText = "</name>"
                    End If
                    If intColCnt = 1 Then
                        printText = "</value>"
                    End If
                    If intColCnt > 1 Then
                        printText = "</description>"
                    End If
                    'Print #intLogFile, printText; vbCr;
                    '----------------------
                    intColCnt = intColCnt + 1
                Next iCell
                printText = "</field>"
            Print #intLogFile, "  "; printText; vbCr;
            End If
            intRowCnt = intRowCnt + 1
        Next iRow
        printText = "</message>"
    Print #intLogFile, printText; vbCr;
        '/////////////////////////////////////////////////////
        GoTo GotoNextTable
    End If
writeSecBoardFieldCodeX:
    If writeSecBoardFieldCode <> 0 Then
        '/////////////////////////////////////////////////////
        printText = "<secboardfieldcode>"
    Print #intLogFile, printText; vbCr;
        intRowCnt = 0
        For Each iRow In oTable.Rows
            '----------------------
            'If intRowCnt = 0 Then
            '    printText = "<definition>"
            'End If
            If intRowCnt <> 0 Then
                printText = "<row>"
                'End If
        Print #intLogFile, "  "; printText; vbCr;
                '----------------------
                intColCnt = 0
                For Each iCell In iRow.Cells
                    '----------------------
                    If intColCnt = 0 Then
                        printText = "<code>'"
                    End If
                    If intColCnt = 1 Then
                        printText = "<field>"
                    End If
                    If intColCnt = 2 Then
                        printText = "<type>"
                    End If
                    If intColCnt = 3 Then
                        printText = "<width>"
                    End If
                    If intColCnt = 4 Then
                        printText = "<example>"
                    End If
            Print #intLogFile, "  "; "  "; printText;
                    '----------------------
                    sCellText = iCell.Range
                    sCellText = Left$(sCellText, Len(sCellText) - 2)
                    printText = sCellText
            Print #intLogFile, printText;
                    '----------------------
                    If intColCnt = 0 Then
                        printText = "'</code>"
                    End If
                    If intColCnt = 1 Then
                        printText = "</field>"
                    End If
                    If intColCnt = 2 Then
                        printText = "</type>"
                    End If
                    If intColCnt = 3 Then
                        printText = "</width>"
                    End If
                    If intColCnt = 4 Then
                        printText = "</example>"
                    End If
            Print #intLogFile, printText; vbCr;
                    '----------------------
                    intColCnt = intColCnt + 1
                Next iCell
                '----------------------
                'If intRowCnt = 0 Then
                '    printText = "</definition>"
                'End If
                'If intRowCnt <> 0 Then
                printText = "</row>"
                'End If
        Print #intLogFile, "  "; printText; vbCr;
                '----------------------
            End If
            intRowCnt = intRowCnt + 1
        Next iRow
        printText = "</secboardfieldcode>"
    Print #intLogFile, printText; vbCr;
        '/////////////////////////////////////////////////////
        GoTo GotoNextTable
    End If
writeOkRepX:
    If writeOkRep <> 0 Then

        GoTo GotoNextTable
    End If
writeBadRepX:
    If writeBadRep <> 0 Then

        GoTo GotoNextTable
    End If

PrintTables:
    If comesFromCall <> 0 Then
        Debug.Print ("table.started to print_" & CStr(messageCount))
        printText = "<message>"
    Print #intLogFile, printText; vbCr;
        ''''--------------
    Print #intLogFile, "  "; "<feature>"; vbCr;
    Print #intLogFile, "  "; "  "; "name="""; "order"; """"; vbCr; '"</name>"
    Print #intLogFile, "  "; "  "; "value="""; CStr(messageCount); """"; vbCr; ' "</value>"
    Print #intLogFile, "  "; "</feature>"; vbCr;
        ''''-------------
        ''''--------------
    Print #intLogFile, "  "; "<feature>"; vbCr;
    Print #intLogFile, "  "; "  "; "name="""; "tablecnt"; """"; vbCr; '"</name>"
    Print #intLogFile, "  "; "  "; "value="""; CStr(tableCount); """"; vbCr; ' "</value>"
    Print #intLogFile, "  "; "</feature>"; vbCr;
        ''''-------------
        'printText = "<order>" & CStr(messageCount) & "</order>"
        'Print #intLogFile, "  "; printText; vbCr;

        intRowCnt = 0
        If reqRep = 0 Then
            'printText = "<requestReplyType>Request</requestReplyType>"
            ''''--------------
    Print #intLogFile, "  "; "<feature>"; vbCr;
    Print #intLogFile, "  "; "  "; "name="""; "requestReplyType"; """"; vbCr; ' "</name>"
    Print #intLogFile, "  "; "  "; "value="""; "Request"; """"; vbCr; '"</value>"
    Print #intLogFile, "  "; "</feature>"; vbCr;
            ''''-------------
        End If
        If reqRep > 0 Then
            'printText = "<requestReplyType>Reply</requestReplyType>"
            'Print #intLogFile, "  "; printText; vbCr;
            ''''--------------
    Print #intLogFile, "  "; "<feature>"; vbCr;
    Print #intLogFile, "  "; "  "; "name="""; "requestReplyType"; """"; vbCr; '"</name>"
    Print #intLogFile, "  "; "  "; "value="""; "Reply"; """"; vbCr; '"</value>"
    Print #intLogFile, "  "; "</feature>"; vbCr;
            ''''-------------
            ''printText = "<replyIndex>" & CStr(reqRep) & "</replyIndex>"
            ''''--------------
    Print #intLogFile, "  "; "<feature>"; vbCr;
    Print #intLogFile, "  "; "  "; "name="""; "replyIndex"; """"; vbCr; ' "</name>"
    Print #intLogFile, "  "; "  "; "value="""; CStr(reqRep); """"; vbCr; ' "</value>"
    Print #intLogFile, "  "; "</feature>"; vbCr;
            ''''-------------
        End If
        'If reqRep > 1 Then
        'printText = "<requestReplyType>Reply</requestReplyType>"
        'Print #intLogFile, "  "; printText; vbCr;
        'printText = "<replyIndex>" & CStr(reqRep) & "</replyIndex>"
        'End If
        'Print #intLogFile, "  "; printText; vbCr;

        'printText = "<msgtype>" & strMsgType & "</msgtype>"
        'Print #intLogFile, "  "; printText; vbCr;
        ''''--------------
    Print #intLogFile, "  "; "<feature>"; vbCr;
    Print #intLogFile, "  "; "  "; "name="""; "category"; """"; vbCr; '"</name>"
    Print #intLogFile, "  "; "  "; "value="""; strMsgType; """"; vbCr; ' "</value>"
    Print #intLogFile, "  "; "</feature>"; vbCr;
        ''''-------------
        messageCount = messageCount + 1
        reqRep = reqRep + 1
        For Each iRow In tHeader.Rows
            '----------------------
            If intRowCnt <> 0 Then
                printText = "<definition_with_error>"
            End If
            If intRowCnt = 0 Then
                printText = "<definition>"
            End If
            'Print #intLogFile, "  "; printText; vbCr;
            '----------------------
            intColCnt = 0

            cell1 = iRow.Cells(1).Range
            cell2 = iRow.Cells(2).Range
            cell1 = Left$(cell1, Len(cell1) - 2)
            cell2 = Left$(cell2, Len(cell2) - 2)
            If cell1 <> "" And cell2 <> "" Then
                For Each iCell In iRow.Cells
                    '----------------------
                    If intColCnt = 0 Then
                        printText = "classname"
                    End If
                    If intColCnt = 1 Then
                        printText = "messagetype"
                    End If
                    If intColCnt >= 2 Then
                        printText = "deff_error"
                    End If
                    'Print #intLogFile, "  "; "  "; printText;
                    ''''--------------
                    Print #intLogFile, "  "; "<feature>"; vbCr;
                     Print #intLogFile, "  "; "  "; "name="""; printText; """"; vbCr; '"</name>"

                    'Print #intLogFile, "  "; "  "; printText;
                    '---------------------
                    'Print #intLogFile, "  "; "  "; printText;
                    '----------------------

                    sCellText = iCell.Range
                    sCellText = Left$(sCellText, Len(sCellText) - 2)
                    printText = RTrim(sCellText)
                    hold = printText

                    If msgtype = 1 And intColCnt = 1 Then
                        printText = "MSGTYPE_OPERATOR_MSG(0x8e)"
                    End If

                    'Print #intLogFile, printText;
                    Print #intLogFile, "  "; "  "; "value="""; printText; """"; vbCr; '"</value>"
                    Print #intLogFile, "  "; "</feature>"; vbCr;

                    '----------------------
                    If intColCnt = 0 Then
                        printText = "</name>"
                    End If
                    If intColCnt = 1 Then
                        printText = "</type>"
                    End If
                    If intColCnt >= 2 Then
                        printText = "</deff_error>"
                    End If
                    'Print #intLogFile, printText; vbCr;
                    '----------------------
                    intColCnt = intColCnt + 1
                Next iCell
            End If

            '----------------------
            If intRowCnt <> 0 Then
                printText = "</definition_with_error>"
            End If
            If intRowCnt = 0 Then
                printText = "</definition>"
            End If
            'Print #intLogFile, "  "; printText; vbCr;
            '----------------------
            intRowCnt = intRowCnt + 1
        Next iRow

        intRowCnt = 0

        If msgtype = 1 Then
            '----------------------
            'printText = "<operatorMsgType>"
            'Print #intLogFile, "  "; printText;
            ''''--------------
        Print #intLogFile, "  "; "<feature>"; vbCr;
        Print #intLogFile, "  "; "  "; "name="""; "operatorMsgType"; """"; vbCr; '"</name>"
        Print #intLogFile, "  "; "  "; "value="""; hold; """"; vbCr; '"</value>"
        Print #intLogFile, "  "; "</feature>"; vbCr;
            ''''-------------
            '& hold & "</field>"
            'printText = "<Field Name>" & hold & "</Field Name>"
            'Print #intLogFile, "  "; "  "; printText; vbCr;

            'printText = "<Mand.>Y</Mand.>"
            'Print #intLogFile, "  "; "  "; printText; vbCr;

            'printText = "<Length>char</Length>"
            'Print #intLogFile, "  "; "  "; printText; vbCr;

            'printText = "<Description>Operator Message Type</Description>"
            'Print #intLogFile, "  "; "  "; printText; vbCr;

            printText = "</operatorMsgType>"
            'Print #intLogFile, hold; printText; vbCr;
            '----------------------
        End If
        
        defineFieldMessage = 0
        
        For Each iRow In tDetail.Rows
            intColCnt = 0

            If intRowCnt <> 0 Then
                '----------------------
                printText = "<field>"
                Print #intLogFile, "  "; printText; vbCr;
                '----------------------

                For Each iCell In iRow.Cells
                    '----------------------
                    If intColCnt = 0 Then
                        printText = "name" ' + c1Name + ">"
                    End If
                    If intColCnt = 1 Then
                        printText = "mandatory" '+ c2Name + ">"
                    End If
                    If intColCnt = 2 Then
                        printText = "length" '+ c3Name + ">"
                    End If
                    If intColCnt = 3 Then
                        printText = "description" '+ c4Name + ">"
                    End If
                    If intColCnt > 3 Then
                        printText = "field_error"
                    End If
                    'Print #intLogFile, "  "; "  "; printText;
                    '----------------------
                    ''''--------------
                    Print #intLogFile, "  "; "  "; "<feature>"; vbCr;
                    Print #intLogFile, "  "; "  "; "  "; "name="""; printText; """"; vbCr; '"</name>"

                    ''''-------------
                    sCellText = iCell.Range
                    sCellText = Left$(sCellText, Len(sCellText) - 2)
                    printText = RTrim(sCellText)
                    If intColCnt = 0 Then
                        c5Name = printText
                    End If
                    If intColCnt = 2 Then
                        If IsNumeric(printText) = True Then
                           defineFieldMessage = 1
                           printText = "LEN_AUTO_DEF_" & CStr(autoDefCnt1) & c5Name
                           autoDefCnt1 = autoDefCnt1 + 1
                        End If
                    End If
                    
                    'Print #intLogFile, printText;
                    Print #intLogFile, "  "; "  "; "  "; "value="""; printText; """"; vbCr; '"</value>"
                    Print #intLogFile, "  "; "  "; "</feature>"; vbCr;
                    '----------------------
                    '----------------------
                    If intColCnt = 0 Then
                        printText = "<name>" ' + c1Name + ">"
                    End If
                    If intColCnt = 1 Then
                        printText = "<mandatory>" '+ c2Name + ">"
                    End If
                    If intColCnt = 2 Then
                        printText = "<length>" '+ c3Name + ">"
                    End If
                    If intColCnt = 3 Then
                        printText = "<description>" '+ c4Name + ">"
                    End If
                    If intColCnt > 3 Then
                        printText = "</field_error>"
                    End If
                    'Print #intLogFile, printText; vbCr;
                    '----------------------
                    '----------------------
                    intColCnt = intColCnt + 1
                Next iCell
                '----------------------
                printText = "</field>"
        Print #intLogFile, "  "; printText; vbCr;
                '----------------------
            End If

            intRowCnt = intRowCnt + 1
        Next iRow

        printText = "</message>"
    Print #intLogFile, printText; vbCr;
''############################################################################
If defineFieldMessage <> 0 Then
        printText = "<message>"
        Print #intLogFile, printText; vbCr;
        ''''--------------
        Print #intLogFile, "  "; "<feature>"; vbCr;
        Print #intLogFile, "  "; "  "; "name="""; "category"; """"; vbCr; '"</name>"
        Print #intLogFile, "  "; "  "; "value="""; "fielddef"; """"; vbCr; ' "</value>"
        Print #intLogFile, "  "; "</feature>"; vbCr;
        ''''-------------
        For Each iRow In tDetail.Rows
            intColCnt = 0

            If intRowCnt <> 0 Then
                cell1 = iRow.Cells(1).Range
                cell2 = iRow.Cells(3).Range
                cell3 = iRow.Cells(4).Range
                cell1 = Left$(cell1, Len(cell1) - 2)
                cell2 = Left$(cell2, Len(cell2) - 2)
                cell3 = Left$(cell3, Len(cell3) - 2)
                If IsNumeric(cell2) = True Then
                        
                ''//////////
                printText = "<field>"
                Print #intLogFile, "  "; printText; vbCr;
                
                Print #intLogFile, "  "; "<feature>"; vbCr;
                Print #intLogFile, "  "; "  "; "name="""; "name"; """"; vbCr; '"</name>"
                Print #intLogFile, "  "; "  "; "value="""; "LEN_AUTO_DEF_" & CStr(autoDefCnt) & cell1; """"; vbCr; ' "</value>"
                Print #intLogFile, "  "; "</feature>"; vbCr;
                Debug.Print "field type defined: LEN_" & cell1 & " lenght: " & cell2
                
                Print #intLogFile, "  "; "<feature>"; vbCr;
                Print #intLogFile, "  "; "  "; "name="""; "value"; """"; vbCr; '"</name>"
                Print #intLogFile, "  "; "  "; "value="""; cell2; """"; vbCr;  ' "</value>"
                Print #intLogFile, "  "; "</feature>"; vbCr;
                
                Print #intLogFile, "  "; "<feature>"; vbCr;
                Print #intLogFile, "  "; "  "; "name="""; "description"; """"; vbCr; '"</name>"
                Print #intLogFile, "  "; "  "; "value="""; cell3; """"; vbCr;  ' "</value>"
                Print #intLogFile, "  "; "</feature>"; vbCr;
                printText = "</field>"
                Print #intLogFile, "  "; printText; vbCr;
                autoDefCnt = autoDefCnt + 1
                End If
            End If

            intRowCnt = intRowCnt + 1
        Next iRow

        printText = "</message>"
    Print #intLogFile, printText; vbCr;
End If
''##################################################################################################

        GoTo GotoNextTable
    End If

    Close #intLogFile

ErrorHandler:
    If Err <> 0 Then
        Dim Msg As String
        Msg = "Error # " & Str(Err.Number) & Chr(13) & Err.Description _
        & Chr(13) & "Make sure there is a table in the current document."
        'MsgBox(Msg, , "Error")
    End If
    Debug.Print (" End of program ")
End Sub








