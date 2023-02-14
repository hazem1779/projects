clc;
clear;
   %% PHASE B

%  for i = 1:11  
%     p=0:0.001:0.01;
%     y=p(i);
%     x =50 ;
%     sim ('IEEE9Bus_new.slx');
%     
%     % ------------------------------- LINE 7-8 -------------------------------
%     [c,l] = wavedec(Ib_78, 4, 'db4');   d1_Ib78 = wrcoef('d',c,l,'db4',1);
%     [c,l] = wavedec(Ib_87, 4, 'db4');   d1_Ib87 = wrcoef('d',c,l,'db4',1);
% 
%     m_78(i)=max(d1_Ib78(600:800));
%     m_87(i)=max(d1_Ib87(600:800));
%  end
%  f=0.03:0.001:0.04;
%  plot(f,m_78,'-o',f,m_87,'-o','linewidth',2)
%  xlim([0.03 0.04])
%  legend('I78','I87')
%  title('LINE 7-8')

%     % ------------------------------- LINE 8-9 -------------------------------
%     [c,l] = wavedec(Ib_89, 4, 'db4');   d1_Ib89 = wrcoef('d',c,l,'db4',1);
%     [c,l] = wavedec(Ib_98, 4, 'db4');   d1_Ib98 = wrcoef('d',c,l,'db4',1);
% 
%     sp2 = subplot(3,2,2);
%     plot(tout,d1_Ib89,tout,d1_Ib98,'linewidth',1)
%     legend('I89','I98')
%     title('LINE 8-9')
% 
%     % ------------------------------- LINE 7-5 -------------------------------
%     [c,l] = wavedec(Ib_57, 4, 'db4');   d1_Ib57 = wrcoef('d',c,l,'db4',1);
%     [c,l] = wavedec(Ib_75, 4, 'db4');   d1_Ib75 = wrcoef('d',c,l,'db4',1);
% 
%     sp3 = subplot(3,2,3);
%     plot(tout,d1_Ib57,tout,d1_Ib75,'linewidth',1)
%     legend('I57','I75')
%     title('LINE 7-5')
% 
%     % ------------------------------- LINE 9-6 -------------------------------
%     [c,l] = wavedec(Ib_69, 4, 'db4');   d1_Ib69 = wrcoef('d',c,l,'db4',1);
%     [c,l] = wavedec(Ib_96, 4, 'db4');   d1_Ib96 = wrcoef('d',c,l,'db4',1);
% 
%     sp4 = subplot(3,2,4);
%     plot(tout,d1_Ib69,tout,d1_Ib96,'linewidth',1)
%     legend('I69','I96')
%     title('LINE 9-6')
% 
%     % ------------------------------- LINE 5-4 -------------------------------
%     [c,l] = wavedec(Ib_45, 4, 'db4');   d1_Ib45 = wrcoef('d',c,l,'db4',1);
%     [c,l] = wavedec(Ib_54, 4, 'db4');   d1_Ib54 = wrcoef('d',c,l,'db4',1);
% 
%     sp5 = subplot(3,2,5);
%     plot(tout,d1_Ib45,tout,d1_Ib54,'linewidth',1)
%     legend('I45','I54')
%     title('LINE 5-4')
% 
%     % ------------------------------- LINE 6-4 -------------------------------
%     [c,l] = wavedec(Ib_46, 4, 'db4');   d1_Ib46 = wrcoef('d',c,l,'db4',1);
%     [c,l] = wavedec(Ib_64, 4, 'db4');   d1_Ib64 = wrcoef('d',c,l,'db4',1);
% 
%     sp6 = subplot(3,1,6);
%     plot(tout,d1_Ib46,tout,d1_Ib64,'linewidth',1)
%     legend('I46','I64')
%      title('LINE 6-4')
% 
% 
%     t = ['\it{LG fault, phase b coefficients fault at}',num2str(x),'% \it{of Line 7-8,  R_f = 0.01 \Omega}'];
%     sgtitle({'\bf{Level 1 Detailed CoeffIbients}\rm',t},'FontName','Times New Roman')
%     linkaxes([sp1 sp2 sp3 sp4 sp5 sp6],'xy')
%     
%     set(gcf,'Renderer','Painters')

     
%     saveas(gcf,['LG_',num2str(x),'%_Rf0.01.fig'],'fig')
%     
%     
%     [max_d78(1), I_max_d78(1)] = max(d1_Ib78);
%     [max_d87(1), I_max_d87(1)] = max(d1_Ib87);
%      
%     P_M_I_78(1,:) = [x  max_d78(1)  I_max_d78(1)];
%     P_M_I_87(1,:) = [x  max_d87(1)  I_max_d87(1)];
% 
%     save('P_M_I_78.mat') 
%     save('P_M_I_87.mat') 
%     
%     pause(4)
%     clc;
%     clearvars -except  P_M_I_78  P_M_I_87;
   
    
    
    
    
    %% PHASE A
    %% 
    
    x = 50 ;
    sim ('IEEE9Bus_new.slx');
    figure
   
   
    
    % ------------------------------- LINE 7-8 -------------------------------
    [c,l] = wavedec(Ia_78, 4, 'db4');   d1_Ia78 = wrcoef('d',c,l,'db4',1);
    [c,l] = wavedec(Ia_87, 4, 'db4');   d1_Ia87 = wrcoef('d',c,l,'db4',1);
    
    subplot(2,1,1)
    plot(tout, d1_Ia78,'linewidth',2)
    xlim([0.028 0.032])
    legend('I78')
    title('Fault A-G LINE 7-8')
    subplot(2,1,2)
    plot(tout, d1_Ia87, 'r','linewidth',2)
    xlim([0.028 0.032])
    legend('I87')
    
% 
%     % ------------------------------- LINE 8-9 -------------------------------
%     [c,l] = wavedec(Ia_89, 4, 'db4');   d1_Ia89 = wrcoef('d',c,l,'db4',1);
%     [c,l] = wavedec(Ia_98, 4, 'db4');   d1_Ia98 = wrcoef('d',c,l,'db4',1);
% 
%     sp2 = subplot(3,2,2);
%     plot(tout,d1_Ia89,tout,d1_Ia98,'linewidth',1)
%     legend('I89','I98')
%     title('LINE 8-9')
% 
%     % ------------------------------- LINE 7-5 -------------------------------
%     [c,l] = wavedec(Ia_57, 4, 'db4');   d1_Ia57 = wrcoef('d',c,l,'db4',1);
%     [c,l] = wavedec(Ia_75, 4, 'db4');   d1_Ia75 = wrcoef('d',c,l,'db4',1);
% 
%     sp3 = subplot(3,2,3);
%     plot(tout,d1_Ia57,tout,d1_Ia75,'linewidth',1)
%     legend('I57','I75')
%     title('LINE 7-5')
% 
%     % ------------------------------- LINE 9-6 -------------------------------
%     [c,l] = wavedec(Ia_69, 4, 'db4');   d1_Ia69 = wrcoef('d',c,l,'db4',1);
%     [c,l] = wavedec(Ia_96, 4, 'db4');   d1_Ia96 = wrcoef('d',c,l,'db4',1);
% 
%     sp4 = subplot(3,2,4);
%     plot(tout,d1_Ia69,tout,d1_Ia96,'linewidth',1)
%     legend('I69','I96')
%     title('LINE 9-6')
% 
%     % ------------------------------- LINE 5-4 -------------------------------
%     [c,l] = wavedec(Ia_45, 4, 'db4');   d1_Ia45 = wrcoef('d',c,l,'db4',1);
%     [c,l] = wavedec(Ia_54, 4, 'db4');   d1_Ia54 = wrcoef('d',c,l,'db4',1);
% 
%     sp5 = subplot(3,2,5);
%     plot(tout,d1_Ia45,tout,d1_Ia54,'linewidth',1)
%     legend('I45','I54')
%     title('LINE 5-4')
% 
%     % ------------------------------- LINE 6-4 -------------------------------
%     [c,l] = wavedec(Ia_46, 4, 'db4');   d1_Ia46 = wrcoef('d',c,l,'db4',1);
%     [c,l] = wavedec(Ia_64, 4, 'db4');   d1_Ia64 = wrcoef('d',c,l,'db4',1);
% 
%     sp6 = subplot(3,2,6);
%     plot(tout,d1_Ia46,tout,d1_Ia64,'linewidth',1)
%     legend('I46','I64')
%     title('LINE 6-4')
% 
%  
%     t = ['\it{AB-G fault, phase A coefficients fault at }',num2str(x),'% \it{of Line 7-8,  R_f = 0.01 \Omega}'];
%     sgtitle({'\bf{Level 1 Detailed CoeffIbients}\rm',t},'FontName','Times New Roman')
%     linkaxes([sp1 sp2 sp3 sp4 sp5 sp6],'xy')
%     sp1.XLim = [0.033 0.04]
%     set(gcf,'Renderer','Painters')
%     
%     %% PHASE C
%     x = 50 ;
%     sim ('IEEE9Bus_new.slx');
%     figure
%    
%    
%     
%     % ------------------------------- LINE 7-8 -------------------------------
%     [c,l] = wavedec(Ic_78, 4, 'db4');   d1_Ic78 = wrcoef('d',c,l,'db4',1);
%     [c,l] = wavedec(Ic_87, 4, 'db4');   d1_Ic87 = wrcoef('d',c,l,'db4',1);
% 
%     sp1 = subplot(3,2,1);
%     plot(tout, d1_Ic78, tout, d1_Ic87,'linewidth',1)
%     legend('I78','I87')
%     title('LINE 7-8')
% 
%     % ------------------------------- LINE 8-9 -------------------------------
%     [c,l] = wavedec(Ic_89, 4, 'db4');   d1_Ic89 = wrcoef('d',c,l,'db4',1);
%     [c,l] = wavedec(Ic_98, 4, 'db4');   d1_Ic98 = wrcoef('d',c,l,'db4',1);
% 
%     sp2 = subplot(3,2,2);
%     plot(tout,d1_Ic89,tout,d1_Ic98,'linewidth',1)
%     legend('I89','I98')
%     title('LINE 8-9')
% 
%     % ------------------------------- LINE 7-5 -------------------------------
%     [c,l] = wavedec(Ic_57, 4, 'db4');   d1_Ic57 = wrcoef('d',c,l,'db4',1);
%     [c,l] = wavedec(Ic_75, 4, 'db4');   d1_Ic75 = wrcoef('d',c,l,'db4',1);
% 
%     sp3 = subplot(3,2,3);
%     plot(tout,d1_Ic57,tout,d1_Ic75,'linewidth',1)
%     legend('I57','I75')
%     title('LINE 7-5')
% 
%     % ------------------------------- LINE 9-6 -------------------------------
%     [c,l] = wavedec(Ic_69, 4, 'db4');   d1_Ic69 = wrcoef('d',c,l,'db4',1);
%     [c,l] = wavedec(Ic_96, 4, 'db4');   d1_Ic96 = wrcoef('d',c,l,'db4',1);
% 
%     sp4 = subplot(3,2,4);
%     plot(tout,d1_Ic69,tout,d1_Ic96,'linewidth',1)
%     legend('I69','I96')
%     title('LINE 9-6')
% 
%     % ------------------------------- LINE 5-4 -------------------------------
%     [c,l] = wavedec(Ic_45, 4, 'db4');   d1_Ic45 = wrcoef('d',c,l,'db4',1);
%     [c,l] = wavedec(Ic_54, 4, 'db4');   d1_Ic54 = wrcoef('d',c,l,'db4',1);
% 
%     sp5 = subplot(3,2,5);
%     plot(tout,d1_Ic45,tout,d1_Ic54,'linewidth',1)
%     legend('I45','I54')
%     title('LINE 5-4')
% 
%     % ------------------------------- LINE 6-4 -------------------------------
%     [c,l] = wavedec(Ic_46, 4, 'db4');   d1_Ic46 = wrcoef('d',c,l,'db4',1);
%     [c,l] = wavedec(Ic_64, 4, 'db4');   d1_Ic64 = wrcoef('d',c,l,'db4',1);
% 
%     sp6 = subplot(3,2,6);
%     plot(tout,d1_Ic46,tout,d1_Ic64,'linewidth',1)
%     legend('I46','I64')
%     title('LINE 6-4')
% 
%     t = ['\it{AB-G fault, phase C coefficients fault at}',num2str(x),'% \it{of Line 7-8,  R_f = 0.01 \Omega}'];
%     sgtitle({'\bf{Level 1 Detailed CoeffIbients}\rm',t},'FontName','Times New Roman')
%     linkaxes([sp1 sp2 sp3 sp4 sp5 sp6],'xy')
%     sp1.XLim = [0.033 0.04];
%     set(gcf,'Renderer','Painters')
    
   
   %%%%%%%%%%%%%%%
   
   



