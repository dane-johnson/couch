%module helpers

%luacode {
function couch.TexturedMesh(meshfile, ...)
   local mesh = couch.Mesh.FromFile(meshfile)
   for i, texturefile in ipairs({...}) do
      local material = couch.Material()
      material.usesTex = true
      material.tex = couch.Texture.FromFile(texturefile)
      mesh:SetMaterial(i - 1, material)
   end
   return mesh
end

} // luacode

// Local Variables:
// mode: poly-swig
// End:
