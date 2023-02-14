clc;
clear;
%open('IEEE9Bus_new.slx');
%sim ('IEEE9Bus_new.slx');



for i=1:11
    f = figure(i);
    p = 0:10:100;
    x = p(i);
    sim ('IEEE9Bus_new.slx');

    %% ------------------------------- LINE 7-8 -------------------------------
    [c,l] = wavedec(Ib_78, 4, 'db4');   d1_Ib78 = wrcoef('d',c,l,'db4',1);
    [c,l] = wavedec(Ib_87, 4, 'db4');   d1_Ib87 = wrcoef('d',c,l,'db4',1);

    sp1 = subplot(3,2,1);
    plot(tout, d1_Ib78, tout, d1_Ib87,'linewidth',1)
    legend('I78','I87')
    title('LINE 7-8')

    %% ------------------------------- LINE 8-9 -------------------------------
    [c,l] = wavedec(Ib_89, 4, 'db4');   d1_Ib89 = wrcoef('d',c,l,'db4',1);
    [c,l] = wavedec(Ib_98, 4, 'db4');   d1_Ib98 = wrcoef('d',c,l,'db4',1);

    sp2 = subplot(3,2,2);
    plot(tout,d1_Ib89,tout,d1_Ib98,'linewidth',1)
    legend('I89','I98')
    title('LINE 8-9')

    %% ------------------------------- LINE 7-5 -------------------------------
    [c,l] = wavedec(Ib_57, 4, 'db4');   d1_Ib57 = wrcoef('d',c,l,'db4',1);
    [c,l] = wavedec(Ib_75, 4, 'db4');   d1_Ib75 = wrcoef('d',c,l,'db4',1);

    sp3 = subplot(3,2,3);
    plot(tout,d1_Ib57,tout,d1_Ib75,'linewidth',1)
    legend('I57','I75')
    title('LINE 7-5')

    %% ------------------------------- LINE 9-6 -------------------------------
    [c,l] = wavedec(Ib_69, 4, 'db4');   d1_Ib69 = wrcoef('d',c,l,'db4',1);
    [c,l] = wavedec(Ib_96, 4, 'db4');   d1_Ib96 = wrcoef('d',c,l,'db4',1);

    sp4 = subplot(3,2,4);
    plot(tout,d1_Ib69,tout,d1_Ib96,'linewidth',1)
    legend('I69','I96')
    title('LINE 9-6')

    %% ------------------------------- LINE 5-4 -------------------------------
    [c,l] = wavedec(Ib_45, 4, 'db4');   d1_Ib45 = wrcoef('d',c,l,'db4',1);
    [c,l] = wavedec(Ib_54, 4, 'db4');   d1_Ib54 = wrcoef('d',c,l,'db4',1);

    sp5 = subplot(3,2,5);
    plot(tout,d1_Ib45,tout,d1_Ib54,'linewidth',1)
    legend('I45','I54')
    title('LINE 5-4')

    %% ------------------------------- LINE 6-4 -------------------------------
    [c,l] = wavedec(Ib_46, 4, 'db4');   d1_Ib46 = wrcoef('d',c,l,'db4',1);
    [c,l] = wavedec(Ib_64, 4, 'db4');   d1_Ib64 = wrcoef('d',c,l,'db4',1);

    sp6 = subplot(3,2,6);
    plot(tout,d1_Ib46,tout,d1_Ib64,'linewidth',1)
    legend('I46','I64')
    title('LINE 6-4')

    %% %%%%%%%%%%%%%%%%
    t = ['\it{LG Fault at }',num2str(x),'% \it{of Line 7-8,  R_f = 0.01 \Omega}'];
    sgtitle({'\bf{Level 1 Detailed CoeffIbients}\rm',t},'FontName','Times New Roman')
    linkaxes([sp1 sp2 sp3 sp4 sp5 sp6],'xy')
    sp1.XLim = [0.032 0.04];
    set(gcf,'Renderer','Painters')
    
    saveas(gcf,['LG_',num2str(x),'%_Rf0.01.fig'],'fig')
    
    
    [max_d78(i), I_max_d78(i)] = max(d1_Ib78);
    [max_d87(i), I_max_d87(i)] = max(d1_Ib87);
    
    P_M_I_78(i,:) = [x  max_d78(i)  I_max_d78(i)];
    P_M_I_87(i,:) = [x  max_d87(i)  I_max_d87(i)];

    save('P_M_I_78.mat') 
    save('P_M_I_87.mat') 
    
    pause(4)
    clc;
    clearvars -except  P_M_I_78  P_M_I_87;
    %%%%%%%%%%%%%%%%%%

end

