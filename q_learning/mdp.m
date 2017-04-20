T = [0.05 ,0.05,0.9;
    0.25,0.5,0.25;
    0.01,0.02,0.97];

% T = [0.9,0.25,0.97;
%     0.05,0.5,0.02;
%     0.05,0.25,0.01];
%  T=T';
R = [1;-1;0];

V=[0;  %For
   0;   %Against
   0];  %None


discount = 0.5;

% Actions Balanced =1 , Offensive =2, defensive =3
% Let Default policy be attack in all states (chosed randomly)
policy=[2,2,2];

for i=1:size(policy,2)
    V2(i) = T(policy(i),:)*(R + discount*V);
end

 for i=1:size(policy,2)
     bestQ = -99999;
     arg = 0;
     for j=1:size(T,1)
        Q = T(j,:)*(R + discount*V2');
        if Q> bestQ
            bestQ=Q;
            arg=j;
        end
     end
     policy(i)=arg;
 end

 for i=1:size(policy,2)
     V3(i) = T(policy(i),:)*(R + discount*V2');
 end
 
  for i=1:size(policy,2)
     bestQ = -99999;
     arg = 0;
     for j=1:size(T,1)
        Q = T(j,:)*(R + discount*V3');
        if Q> bestQ
            bestQ=Q;
            arg=j;
        end
     end
     policy(i)=arg;
  end
  
policy