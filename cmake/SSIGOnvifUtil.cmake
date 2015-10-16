macro(ssigonvif_append_target_property target property str) 
  get_target_property(current_property ${target} ${property}) 
  if(NOT current_property) # property non-existent or empty 
      set_target_properties(${target} PROPERTIES ${property} ${str}) 
  else() 
      set_target_properties(${target} PROPERTIES ${property} "${current_property} ${str}") 
  endif() 
endmacro()